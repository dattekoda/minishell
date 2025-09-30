/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 19:51:19 by khanadat         ###   ########.fr       */
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

void    set_redirect(t_red *red, int *cfd)
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
			// start_heredoc();
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
	int	 cfd[2];

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	cfd[0] = STDIN_FILENO;
	cfd[1] = STDOUT_FILENO;
	set_redirect(node->red, cfd);
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
