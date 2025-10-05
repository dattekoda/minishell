/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:12 by khanadat         ###   ########.fr       */
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
#include "ast.h"
#include "set_redirect.h"
#include "builtin.h"

size_t	count_word(t_word *head)
{
	size_t	len;

	len = 0;
	while (head)
		head = (len++, head->next);
	return (len);
}

int	store_argv(t_word *head, char ***argv)
{
	size_t	i;

	*argv = ft_calloc \
	(count_word(head) + 1, sizeof(char *));
	if (!*argv)
		return (ERR);
	i = 0;
	while (head)
	{
		(*argv)[i++] = head->word;
		head = head->next ;
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

int	set_abs_path(char **dir)
{
	size_t	i;
	size_t	dir_len;
	size_t	pwd_len;
	char	*abs_path;
	char	*pwd;

	if (**dir == '/')
	{
		*dir = ft_strdup(*dir);
		if (!*dir)
			return (ERR);
		return (SUCCESS);
	}
	dir_len	= ft_strlen(*dir);
	pwd = mini_getcwd();
	pwd_len = ft_strlen(pwd);
	abs_path = ft_calloc(dir_len + pwd_len + 2, sizeof(char));
	if (!abs_path)
		return (ERR);
	i = 0;
	ft_memmove(abs_path + i, pwd, pwd_len);
	i += pwd_len;
	ft_memmove(abs_path + i, "/", 1);
	i += 1;
	ft_memmove(abs_path + i, *dir, dir_len);
	*dir = abs_path;
	return (SUCCESS);
}

void    exec_child_proc(t_mini *mini, char **argv)
{
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	get_path(&path, mini, argv);
	execve(path, argv, mini->envp);
	exit(0);
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	pid_t	cmd_id;
	int		status;
	char	**argv;
	int	 	cfd[2];
	int		saved[2];

	if (expand_node(node, mini))
		return ;
	if (store_argv(node->word, &argv))
		systemcall_minishell_exit(mini, "malloc");
	cfd[0] = STDIN_FILENO;
	cfd[1] = STDOUT_FILENO;
	if (set_redirect(mini, node->red, cfd))
	{
		close_cfd(cfd);
		return ;
	}
	if (cfd[0] != STDIN_FILENO)
	{
		saved[0] = dup(STDIN_FILENO);
		if (saved[0] < 0)
			systemcall_minishell_exit(mini, "dup");
		dup2(cfd[0], STDIN_FILENO);
	}
	if (cfd[1] != STDOUT_FILENO)
	{
		saved[1] = dup(STDOUT_FILENO);
		if (saved[1] < 0)
			systemcall_minishell_exit(mini, "dup");
		dup2(cfd[1], STDOUT_FILENO);
	}
	if (!exec_builtin(mini, argv))
	{
		cmd_id = fork();
		if (cmd_id < 0)
			systemcall_minishell_exit(mini, "fork");
		if (cmd_id == 0)
			exec_child_proc(mini, argv);
		if (waitpid(cmd_id, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
	}
	if (cfd[0] != STDIN_FILENO)
	{
		close(cfd[0]);
		if (dup2(saved[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(saved[0]);
	}
	if (cfd[1] != STDOUT_FILENO)
	{
		close(cfd[1]);
		if (dup2(saved[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(saved[1]);
	}
	free(argv);
	if (mini->heredoc_name)
	{
		unlink(mini->heredoc_name);
		mini->heredoc_name = NULL;
	}
}

void	exec_prompt(t_mini *mini, t_node *node/* , t_NodeKind nkind */)
{
	if (!node)
		return ;
	if (node->lhs)
		exec_prompt(mini, node->lhs/* , node->kind */);
	if (node->kind == ND_CMD)
		exec_cmd(mini, node);
}
