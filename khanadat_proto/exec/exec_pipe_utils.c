/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:44:49 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 14:16:54 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_utils.h"
#include "exec_utils.h"
#include "ast_define.h"
#include "libft.h"

static t_node	*connect_cmd(t_node *node);
static void		exec_pipe_child(t_mini *mini, t_node *before, t_node *node);

t_node	*set_cmd_order(t_node *node)
{
	connect_cmd(node);
	while (node->lhs)
		node = node->lhs;
	return (node);
}

void	start_pipe_group(t_mini *mini, t_node *node)
{
	t_node	*before;

	before = NULL;
	while (node)
	{
		if (node->rhs)
			pipe(node->cmd->pfd);
		node->cmd->pid = fork();
		if (node->cmd->pid < 0)
			systemcall_minishell_exit(mini, "fork");
		if (node->cmd->pid == 0)
			exec_pipe_child(mini, before, node);
		if (0 < node->cmd->pid && before)
		{
			close(before->cmd->pfd[0]);
			close(before->cmd->pfd[1]);
		}
		before = node;
		node = node->rhs;
	}
}

void	wait_pipe_group(t_mini *mini, t_node *node)
{
	int	status;

	while (node)
	{
		if (waitpid(node->cmd->pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
		node = node->rhs;
	}
}

static t_node	*connect_cmd(t_node *node)
{
	t_node	*tmp;

	if (node->lhs->kind == ND_CMD)
	{
		node->lhs->rhs = node->rhs;
		return (node->lhs);
	}
	if (node->lhs->kind == ND_PIPE)
	{
		tmp = connect_cmd(node->lhs);
		tmp->rhs = node->rhs;
		return (node->rhs);
	}
	return (NULL);
}

static void	exec_pipe_child(t_mini *mini, t_node *before, t_node *node)
{
	if (before)
	{
		close(before->cmd->pfd[1]);
		if (dup2(before->cmd->pfd[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(before->cmd->pfd[0]);
	}
	if (node->rhs)
	{
		close(node->cmd->pfd[0]);
		if (dup2(node->cmd->pfd[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(node->cmd->pfd[1]);
	}
	if (mini->signaled)
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
	exec_cmd(mini, node);
}
