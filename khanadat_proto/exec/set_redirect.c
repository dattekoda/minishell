/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:18:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/10 08:55:56 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "libft.h"
#include "set_redirect_utils.h"

void	start_heredoc(t_mini *mini, t_red *red, int fd)
{
	char	*line;
	int		status;
	size_t	len;

	set_handler(SIGINT, SIG_DFL);
	len = ft_strlen(red->file);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		status = ft_get_next_line(STDIN_FILENO, &line);
		if (status == -1)
			exit((err_system_call("read"), SYSTEMCALL_EXITSTATUS));
		else if (status == -2)
			exit((err_system_call("malloc"), SYSTEMCALL_EXITSTATUS));
		if (!line)
			exit((err_heredoc(red->file), NO_ERR));
		if (expand_dollar(mini, &line))
			exit((free(line), SYSTEMCALL_EXITSTATUS));
		if (!ft_strncmp(line, red->file, len) && line[len] == '\n')
			exit((free(line), SUCCESS));
		ft_putstr_fd(line, fd);
		free(line);
	}
}

int	mini_heredoc(t_mini *mini, t_red *red, t_cmd *cmd)
{
	int		status;
	pid_t	heredoc_id;
	int		fd;
	char	*hd_name;

	safe_delete_heredoc_file(cmd);
	hd_name = set_heredoc_name(0);
	if (!hd_name)
		systemcall_minishell_exit(mini, "malloc");
	fd = open(hd_name, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd < 0)
		systemcall_minishell_exit((free(hd_name), mini), hd_name);
	heredoc_id = fork();
	if (heredoc_id < 0)
		systemcall_minishell_exit((close(fd), free(hd_name), mini), "fork");
	if (heredoc_id == 0)
		start_heredoc(mini, red, fd);
	if (waitpid(heredoc_id, &status, 0) < 0)
		systemcall_minishell_exit(mini, "waitpid");
	catch_signal(status, mini);
	close(fd);
	cmd->heredoc_name = hd_name;
	if (WIFSIGNALED(status))
		return (safe_delete_heredoc_file(cmd), FAILURE);
	return (SUCCESS);
}

int	set_redirect_in(t_mini *mini, t_red *red, t_cmd *cmd)
{
	char	*file_name;

	if (cmd->rfd[0] != FD_DFL)
		close(cmd->rfd[0]);
	if (red->kind == RD_HEREDOC)
		file_name = cmd->heredoc_name;
	if (red->kind == RD_IN)
		file_name = red->file;
	cmd->rfd[0] = open(file_name, O_RDONLY);
	if (cmd->rfd[0] == -1)
		return (err_file(file_name), \
		store_status(FAILURE, mini), FAILURE);
	return (SUCCESS);
}

int	set_redirect(t_mini *mini, t_red *red, t_cmd *cmd)
{
	while (red)
	{
		if (red->kind == RD_OUT || red->kind == RD_APPEND)
		{
			if (cmd->rfd[1] != FD_DFL)
				close(cmd->rfd[1]);
			cmd->rfd[1] = open(red->file, \
				O_RDWR | O_CREAT | \
				O_APPEND * (red->kind == RD_APPEND) | \
				O_TRUNC * (red->kind == RD_OUT), 0666);
			if (cmd->rfd[1] == -1)
				return (err_file(red->file), \
				store_status(FAILURE, mini), FAILURE);
		}
		else if (red->kind == RD_IN || red->kind == RD_HEREDOC)
		{
			if (set_redirect_in(mini, red, cmd))
				return (FAILURE);
		}
		red = red->next ;
	}
	return (SUCCESS);
}

int	write_heredoc(t_mini *mini, t_red *red, t_cmd *cmd)
{
	while (red)
	{
		if (red->kind == RD_HEREDOC)
			if (mini_heredoc(mini, red, cmd))
				return (FAILURE);
		red = red->next;
	}
	return (SUCCESS);
}
