/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:08:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/10 08:42:54 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "exec_utils.h"
#include "libft.h"
#include "expand.h"
#include "builtin.h"
#include "set_redirect.h"

static void	exec_pipe_cmd_pipe(t_mini *mini, t_node *node, \
	int *pp, pid_t ret);
static void	exec_pipe_cmd(t_mini *mini, t_node *node);
static void	expand_pipe_group(t_mini *mini, t_node *node);
static void	exec_nd_cmd(t_mini *mini, t_node *node);

void	exec_node(t_mini *mini, t_node *node)
{
	expand_pipe_group(mini, node);
	if (node->kind == ND_PIPE)
	{
		mini->is_pipe = true;
		node->rhs->cmd->pid = fork();
		if (node->rhs->cmd->pid < 0)
			systemcall_minishell_exit(mini, "fork");
		if (node->rhs->cmd->pid == 0)
			exec_pipe_cmd(mini, node);
		else
			wait_pipe(mini, node->rhs);
		mini->is_pipe = false;
	}
	if (node->kind == ND_CMD)
		exec_nd_cmd(mini, node);
	mini->signaled = false;
}

static void	exec_pipe_cmd_pipe(t_mini *mini, t_node *node, \
	int *pp, pid_t ret)
{
	if (ret < 0)
		systemcall_minishell_exit(mini, "fork");
	if (ret == 0)
	{
		close(pp[0]);
		if (dup2(pp[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(pp[1]);
		exec_pipe_cmd(mini, node->lhs);
	}
	else
	{
		close(pp[1]);
		if (dup2(pp[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(pp[0]);
		if (mini->signaled)
			normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
		exec_cmd(mini, node->rhs);
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
	}
}

static void	exec_pipe_cmd(t_mini *mini, t_node *node)
{
	int		pp[2];
	pid_t	ret;

	if (node->kind == ND_CMD)
	{
		exec_cmd(mini, node);
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
	}
	else
	{
		pipe(pp);
		ret = fork();
		exec_pipe_cmd_pipe(mini, node, pp, ret);
	}
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
		wait_pipe(mini, node);
		return ;
	}
	node->cmd->pid = fork();
	if (node->cmd->pid < 0)
		systemcall_minishell_exit(mini, "fork");
	if (node->cmd->pid == 0)
		exec_child_proc(mini, node->cmd->argv);
	else
		wait_pipe(mini, node);
}
