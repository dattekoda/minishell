/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:44:49 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/14 23:23:21 by khanadat         ###   ########.fr       */
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

t_node	*set_cmd_order(t_node *node)
{
	connect_cmd(node);
	while (node->lhs)
		node = node->lhs;
	return (node);
}

void	start_pipe_group(t_mini *mini, t_node *node)
{
	bool	before;

	before = NULL;
	while (node)
	{
		if (!before)
			pipe(node->cmd->pfd);
		node->cmd->pid = fork();
		if (node->cmd->pid < 0)
			systemcall_minishell_exit(mini, "fork");
		if (node->cmd->pid == 0)
		{
			if (before)
			{
				close(node->cmd->pfd[1]);
			}
			exec_cmd(mini, node);
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
		waitpid(node->cmd->pid, &status, 0);
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
