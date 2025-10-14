/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:01:50 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/14 21:16:39 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "minishell_define.h"
#include "minishell_utils.h"
#include "minishell_err.h"
#include "ast_define.h"
#include "exec_utils.h"
#include "exec.h"
#include "libft.h"

void	exec_inside(t_mini *mini, t_node *node)
{
	pid_t	inside_pid;
	int		status;

	status = 0;
	inside_pid = fork();
	if (inside_pid < 0)
		systemcall_minishell_exit(mini, "fork");
	else if (inside_pid == 0)
	{
		mini->is_inside = true;
		set_handler(mini, SIGINT, SIG_DFL);
		exec_prompt(mini, node);
		normal_minishell_exit(mini, NULL, NULL, \
			ft_atoi(mini->status));
	}
	else
	{
		if (waitpid(inside_pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
	}
}

void	wait_node(t_mini *mini, t_node *node)
{
	int	status;

	if (node->cmd->pid != PID_BUILTIN)
	{
		if (waitpid(node->cmd->pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
	}
	reset_rfd(mini, node);
}
