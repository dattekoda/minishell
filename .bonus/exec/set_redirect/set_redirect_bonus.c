/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:18:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"
#include "libft.h"
#include "set_redirect_utils_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>

static void	start_heredoc(t_mini *mini, t_red *red, int fd);
static void	mini_heredoc(t_mini *mini, t_red *red, t_cmd *cmd, int *status);

static int	set_redirect_in(t_mini *mini, t_red *red, t_cmd *cmd)
{
	char	*file_name;

	if (cmd->rfd[0] != FD_DFL)
		close(cmd->rfd[0]);
	if (red->kind == RD_HEREDOC)
		file_name = cmd->heredoc_name;
	if (red->kind == RD_IN)
		file_name = red->expanded;
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
			cmd->rfd[1] = open(red->expanded, \
				O_RDWR | O_CREAT | \
				O_APPEND * (red->kind == RD_APPEND) | \
				O_TRUNC * (red->kind == RD_OUT), 0666);
			if (cmd->rfd[1] == -1)
				return (err_file(red->expanded), \
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
	int	status;

	status = SUCCESS;
	while (red)
	{
		if (red->kind == RD_HEREDOC)
		{
			mini_heredoc(mini, red, cmd, &status);
			if (WIFSIGNALED(status))
				return (FAILURE);
		}
		red = red->next;
	}
	return (SUCCESS);
}

static void	start_heredoc(t_mini *mini, t_red *red, int fd)
{
	char	*line;

	set_handler(mini, SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit((err_heredoc(red->expanded), NO_ERR));
		if (!ft_strcmp(red->file, line))
			exit((free(line), SUCCESS));
		if (!red->is_quoted && expand_dollar(mini, &line))
			exit((free(line), SYSTEMCALL_EXITSTATUS));
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
}

static void	mini_heredoc(t_mini *mini, t_red *red, t_cmd *cmd, int *status)
{
	pid_t	heredoc_id;
	int		fd;
	char	*hd_name;

	hd_name = NULL;
	safe_delete_heredoc_file(&cmd->heredoc_name);
	hd_name = set_heredoc_name(0);
	if (!hd_name)
	{
		systemcall_minishell_exit(mini, "malloc");
		return ;
	}
	fd = open(hd_name, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd < 0)
		sys_hd_exit(mini, hd_name, fd, "open");
	heredoc_id = fork();
	if (heredoc_id < 0)
		sys_hd_exit(mini, hd_name, fd, "fork");
	if (heredoc_id == 0)
		start_heredoc(mini, red, fd);
	if (waitpid(heredoc_id, status, 0) < 0)
		sys_hd_exit(mini, hd_name, fd, "waitpid");
	close(fd);
	cmd->heredoc_name = hd_name;
	catch_final_status(*status, mini);
}
