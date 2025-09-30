/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/01 01:37:10 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"
#include "expand.h"
#include "get_path.h"

#define FILENAME_DAFAULT_LEN 13
#define HEREDOC_FILENAME "/tmp/.heredoc"

size_t	count_word(t_word *head)
{
	size_t	len;

	len = 0;
	while (head)
		head = (len++, head->next);
	return (len);
}

int	store_argv(t_node *node, char ***argv)
{
	t_word	*cur;
	size_t	i;

	*argv = ft_calloc \
	(count_word(node->word) + 1, sizeof(char *));
	if (!*argv)
		return (ERR);
	cur = node->word;
	i = 0;
	while (cur)
	{
		(*argv)[i++] = cur->word;
		cur = cur->next ;
	}
	return (SUCCESS);
}

void	close_cfd(int *cfd)
{
	if (cfd[0] != STDIN_FILENO)
		close(cfd[0]);
	if (cfd[1] != STDOUT_FILENO)
		close(cfd[1]);
}

char	*set_heredoc_name(void)
{
	static unsigned int	num = 0;
	static char			file_name[FILENAME_MAX];
	int					tmp;
	int					i;

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
		return (set_heredoc_name());
	return (file_name);
}

void    set_redirect(t_mini *mini, t_red *red, int *cfd)
{
	while (red)
	{
		if (red->kind == RD_APPEND)
		{
			if (cfd[1] != STDOUT_FILENO)
				close(cfd[1]);
			cfd[1] = open(red->file, O_RDWR | O_CREAT | O_APPEND , 0666);
		}
		else if (red->kind == RD_HEREDOC)
		{
			if (cfd[0] != STDIN_FILENO)
				close(cfd[0]);
			char	*name;
			char	*line;
			int		status;
			int		fd;
			size_t	len;
			len = ft_strlen(red->file);
			name = set_heredoc_name();
			fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
			while (1)
			{
				ft_putstr_fd("> ", STDOUT_FILENO);
				status = ft_get_next_line(STDIN_FILENO, &line);
				if (status == -1)
					systemcall_minishell_exit(mini, "read");
				else if (status == -2)
					systemcall_minishell_exit(mini, "malloc");
				if (!line)
				{
					err_heredoc(red->file);
					break ;
				}
				if (!ft_strncmp(line, red->file, len) \
					&& line[len] == '\n')
				{
					free(line);
					break ;
				}
				ft_putstr_fd(line, fd);
				free(line);
			}
			close(fd);
			cfd[0] = open(name, O_RDONLY);
			unlink(name);
		}
		else if (red->kind == RD_IN)
		{
			if (cfd[0] != STDIN_FILENO)
				close(cfd[0]);
			if (access(red->file, F_OK))
			{
				err_cmd_not_found(red->file);
				red = red->next ;
				continue ;
			}
			cfd[0] = open(red->file, O_RDONLY);
		}
		else if (red->kind == RD_OUT)
		{
			if (cfd[1] != STDOUT_FILENO)
				close(cfd[1]);
			cfd[1] = open(red->file, O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		red = red->next ;
	}
}

void    exec_child_proc(t_mini *mini, t_node *node)
{
	char	**argv;
	char	*path;
	int	 	cfd[2];

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	cfd[0] = STDIN_FILENO;
	cfd[1] = STDOUT_FILENO;
	set_redirect(mini, node->red, cfd);
	if (cfd[0] != STDIN_FILENO)
		dup2(cfd[0], STDIN_FILENO);
	if (cfd[1] != STDOUT_FILENO)
		dup2(cfd[1], STDOUT_FILENO);
	if (expand_word(node, mini))
		systemcall_minishell_exit(mini, "malloc");
	if (store_argv(node, &argv))
		systemcall_minishell_exit(mini, "malloc");
	get_path(&path, mini, argv);
	execve(path, argv, mini->envp);
	exit(0);
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	pid_t	cmd_id;
	int		status;

	cmd_id = fork();
	if (cmd_id < 0)
		systemcall_minishell_exit(mini, "fork");
	if (cmd_id == 0)
		exec_child_proc(mini, node);
	if (waitpid(cmd_id, &status, 0) < 0)
		systemcall_minishell_exit(mini, "waitpid");
	catch_signal(status, mini);
}

void	exec_prompt(t_mini *mini, t_node *node/* , t_NodeKind nkind */)
{
	if (!node)
		return ;
	if (node->lhs)
		exec_prompt(mini, node->lhs/* , node->kind */);
	else if (node->kind == ND_CMD)
		exec_cmd(mini, node);
}
