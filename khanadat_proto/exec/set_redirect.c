/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:18:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 07:09:10 by khanadat         ###   ########.fr       */
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
#include "status.h"

#define FILENAME_DAFAULT_LEN 13
#define HEREDOC_FILENAME "/tmp/.heredoc"

char	*set_heredoc_name(int num)
{
	char	file_name[FILENAME_MAX];
	int		i;
	int		tmp;

	tmp = num;
	ft_strlcpy(file_name, HEREDOC_FILENAME, FILENAME_MAX);
	i = FILENAME_DAFAULT_LEN;
	if (tmp == 0)
		file_name[i++] = '0';
	while (tmp)
	{
		file_name[i++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	file_name[i] = '\0';
	num++;
	if (!access(file_name, F_OK))
		return (set_heredoc_name(num));
	return (ft_strdup(file_name));
}

void	expand_dollar_ready(t_mini *mini, char *line, \
	size_t *expanded_size, t_list *list)
{
	char	*env_val;

	*expanded_size = 0;
	while (*line)
	{
		if (*line == '$')
		{
			line++;
			env_val = mini_getenv(&line, mini);
			ft_lstadd_back(&list, \
				ft_lstnew(env_val));
			(*expanded_size) += ft_strlen(env_val);
			continue ;
		}
		ft_lstadd_back(&list, ft_lstnew(line));
		while (*line && *line != '$')
		{
			(*expanded_size)++;
			line++;
		}
	}
}

void	expand_dollar_set(t_list *list, char *expanded)
{
	size_t	i;
	t_list	*tmp;
	char	*cur;

	i = 0;
	while (list)
	{
		cur = (char *)list->content;
		while (*cur && *cur != '$')
			expanded[i++] = *(cur++);
		tmp = list;
		list = list->next;
		free(tmp);
	}	
}

int	expand_dollar(t_mini *mini, char **line)
{
	char	*expanded;
	size_t	expanded_size;
	t_list	*list;
	t_list	head;

	if (!ft_strchr(*line, '$'))
		return (SUCCESS);
	ft_bzero(&head, sizeof(t_list));
	list = &head;
	expand_dollar_ready(mini, *line, &expanded_size, list);
	expanded = ft_calloc(expanded_size + 1, sizeof(char));
	if (!expanded)
	{
		ft_lstclear(&head.next, NULL);
		systemcall_minishell_exit(mini, "malloc");
	}
	list = head.next;
	expand_dollar_set(list, expanded);
	free(*line);
	*line = expanded;
	return (SUCCESS);
}

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
			systemcall_minishell_exit(mini, "read");
		else if (status == -2)
			systemcall_minishell_exit(mini, "malloc");
		if (!line)
			failure_minishell_exit(mini, &err_heredoc, red->file, NO_ERR);
		if (expand_dollar(mini, &line))
			systemcall_minishell_exit((free(line), mini), "malloc");
		if (!ft_strncmp(line, red->file, len) && line[len] == '\n')
			normal_minishell_exit(mini, &free, line, SUCCESS);
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

	if (cmd->rfd[0] != STDIN_FILENO)
		close(cmd->rfd[0]);
	if (cmd->heredoc_name)
	{
		unlink(cmd->heredoc_name);
		free(cmd->heredoc_name);
		cmd->heredoc_name = NULL;
	}
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
	if (WIFSIGNALED(status))
		return (ERR);
	cmd->heredoc_name = hd_name;
	cmd->rfd[0] = open(cmd->heredoc_name, O_RDONLY);
	if (cmd->rfd[0] < 0)
		systemcall_minishell_exit(mini, cmd->heredoc_name);
	return (SUCCESS);
}

int	set_redirect(t_mini *mini, t_red *red, t_cmd *cmd)
{
	while (red)
	{
		if (red->kind == RD_APPEND)
		{
			if (cmd->rfd[1] != STDOUT_FILENO)
				close(cmd->rfd[1]);
			cmd->rfd[1] = open(red->file, O_RDWR | O_CREAT | O_APPEND , 0666);
		}
		else if (red->kind == RD_HEREDOC)
		{
			if (mini_heredoc(mini, red, cmd))
				return (ERR);
		}
		else if (red->kind == RD_IN)
		{
			if (cmd->rfd[0] != STDIN_FILENO)
				close(cmd->rfd[0]);
			cmd->rfd[0] = open(red->file, O_RDONLY);
			if (cmd->rfd[0] < 0)
				return (err_file(red->file), \
				store_status(FAILURE, mini), \
				ERR);
		}
		else if (red->kind == RD_OUT)
		{
			if (cmd->rfd[1] != STDOUT_FILENO)
				close(cmd->rfd[1]);
			cmd->rfd[1] = open(red->file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		red = red->next ;
	}
	return (SUCCESS);
}
