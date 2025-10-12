/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 09:45:04 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/12 19:10:53 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <signal.h>
#include <sys/wait.h>
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_lib.h"
#include "ast_define.h"
#include "libft.h"
#include "set_redirect.h"
#include "builtin.h"
#include "get_path.h"

int	store_argv(t_word *head, char ***argv)
{
	size_t	i;
	t_word	*cur;

	i = 0;
	cur = head;
	while (cur)
		cur = (i++, cur->next);
	*argv = ft_calloc(i + 1, sizeof(char *));
	if (!*argv)
		return (ERR);
	i = 0;
	while (head)
	{
		(*argv)[i++] = head->word;
		head = head->next;
	}
	return (SUCCESS);
}

void	exec_child_proc(t_mini *mini, char **argv)
{
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	get_path(&path, mini, argv);
	execve(path, argv, mini->envp);
	systemcall_minishell_exit(mini, "execve");
}

void	set_rfd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->rfd[0] != FD_DFL)
	{
		cmd->saved[0] = dup(STDIN_FILENO);
		if (cmd->rfd[0] != STDOUT_FILENO)
		{
			close(STDIN_FILENO);
			if (dup2(cmd->rfd[0], STDIN_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
		}
	}
	if (cmd->rfd[1] != FD_DFL)
	{
		cmd->saved[1] = dup(STDOUT_FILENO);
		if (cmd->rfd[1] != STDIN_FILENO)
		{
			close(STDOUT_FILENO);
			if (dup2(cmd->rfd[1], STDOUT_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
		}
	}
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	if (set_redirect(mini, node->red, node->cmd))
		return ;
	if (!*node->cmd->argv)
		return ;
	set_rfd(mini, node->cmd);
	if (exec_builtin(mini, node->cmd))
		return ;
	else
		exec_child_proc(mini, node->cmd->argv);
}

void	wait_pipe(t_mini *mini, t_node *node)
{
	int	status;

	if (node->cmd->pid != PID_BUILTIN)
	{
		if (waitpid(node->cmd->pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
	}
	if (node->cmd->rfd[0] != FD_DFL)
	{
		close(node->cmd->rfd[0]);
		if (dup2(node->cmd->saved[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(node->cmd->saved[0]);
	}
	if (node->cmd->rfd[1] != FD_DFL)
	{
		close(node->cmd->rfd[1]);
		if (dup2(node->cmd->saved[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(node->cmd->saved[1]);
	}
}
