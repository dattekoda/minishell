/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:01:50 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 22:34:57 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"
#include "ast_define_bonus.h"
#include "exec_utils_bonus.h"
#include "exec_bonus.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#if defined(__APPLE__)
# define OS_ELF "\xCF\xFA\xED\xFE"
#elif defined(__linux__)
# define OS_ELF "\x7F\x45\x4C\x46"
#endif

#define OS_ELF_LEN 4

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
		catch_final_status(status, mini);
	}
}

void	wait_node(t_mini *mini, t_node *node)
{
	int	status;

	if (node->cmd->pid != PID_BUILTIN)
	{
		if (waitpid(node->cmd->pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_final_status(status, mini);
	}
	reset_rfd(mini, node);
}

int	not_valid_execve_file(t_mini *mini, char *path)
{
	char	buf[16];
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		failure_minishell_exit(&err_file, \
			path, PERMISSION_ERR);
	ft_bzero(&buf, 16);
	if (read(fd, buf, 15) < 0)
	{
		close(fd);
		systemcall_minishell_exit(mini, "read");
	}
	close(fd);
	return ((ft_strncmp(buf, OS_ELF, OS_ELF_LEN) != 0));
}
