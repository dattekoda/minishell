/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:15:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/14 23:05:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_utils.h"
#include "exec_utils.h"
#include "exec_pipe_utils.h"
#include "libft.h"
#include "expand.h"
#include "builtin.h"
#include "set_redirect.h"

static void	exec_nd_cmd(t_mini *mini, t_node *node);
static void	exec_nd_pipe(t_mini *mini, t_node *node);
static void	expand_pipe_group(t_mini *mini, t_node *node);

void	exec_node(t_mini *mini, t_node *node)
{
	if (node->kind == ND_INSIDE)
	{
		exec_inside(mini, node->lhs);
		return ;
	}
	expand_pipe_group(mini, node);
	if (node->kind == ND_CMD)
		exec_nd_cmd(mini, node);
	if (node->kind == ND_PIPE)
	{
		mini->is_pipe = true;
		exec_nd_pipe(mini, node);
		mini->is_pipe = false;
	}
	mini->signaled = false;
}

static void	exec_nd_cmd(t_mini *mini, t_node *node)
{
	if (node->expand_err)
		return ;
	if (mini->signaled)
		return ;
	if (set_redirect(mini, node->red, node->cmd))
		return ;
	if (!*node->cmd->argv)
		return ;
	set_rfd(mini, node->cmd);
	if (exec_builtin(mini, node->cmd))
	{
		reset_rfd(mini, node);
		return ;
	}
	node->cmd->pid = fork();
	if (node->cmd->pid < 0)
		systemcall_minishell_exit(mini, "fork");
	if (node->cmd->pid == 0)
		exec_child_proc(mini, node->cmd->argv);
	else
		wait_node(mini, node);
}

void	exec_nd_pipe(t_mini *mini, t_node *node)
{
	node = set_cmd_order(node);
	while (node)
	{
		fprintf(stderr, "%s ", node->cmd->argv[0]);
		node = node->rhs;
	}
	normal_minishell_exit(mini, NULL, NULL, 0);
	// start_pipe_group(node);
	// wait_pipe_group(node);
}

static void	expand_pipe_group(t_mini *mini, t_node *node)
{
	if (!node)
		return ;
	expand_pipe_group(mini, node->lhs);
	if (node->kind == ND_CMD)
	{
		if (expand_node(node, mini))
		{
			node->expand_err = true;
			store_status(FAILURE, mini);
			return ;
		}
		if (store_argv(node->word, &node->cmd->argv))
			systemcall_minishell_exit(mini, "malloc");
		if (!mini->signaled && write_heredoc(mini, node->red, node->cmd))
		{
			mini->signaled = true;
			return ;
		}
	}
	expand_pipe_group(mini, node->rhs);
}
