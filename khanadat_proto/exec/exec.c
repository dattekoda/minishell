/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:24:59 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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

void	exec_child_proc(t_mini *mini, t_node *node)
{
	char	**argv;
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
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
