/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:44:49 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "exec_utils_bonus.h"
#include "ast_define_bonus.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void		exec_pipe_child(t_mini *mini, t_node *before, t_node *node);

t_node	*set_cmd_order(t_node *node)
{
	t_node	*head;
	t_node	*tail;

	if (node->kind == ND_CMD)
		return (node);
	head = set_cmd_order(node->lhs);
	tail = head;
	while (tail->rhs)
		tail = tail->rhs;
	tail->rhs = node->rhs;
	return (head);
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
		catch_final_status(status, mini);
		node = node->rhs;
	}
}

static void	exec_pipe_child(t_mini *mini, t_node *before, t_node *node)
{
	if (mini->signaled)
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
	if (node->expand_err)
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
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
	exec_cmd(mini, node);
}
