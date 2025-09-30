/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 11:56:55 by khanadat         ###   ########.fr       */
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

void	get_cwd_path(char **path, char **argv, t_mini *mini)
{
	char	path_buffer[PATH_MAX];

	ft_strlcpy(path_buffer, "./", PATH_MAX);
	ft_strlcat(path_buffer, argv[0], PATH_MAX);
	if (access(path_buffer, F_OK))
		child_minishell_exit(mini, err_cmd_not_found, \
		argv, NOT_FOUND_ERR);
	if (access(path_buffer, X_OK))
		child_minishell_exit(mini, err_permission, \
		argv, PERMISSION_ERR);
	*path = ft_strdup(path_buffer);
	if (!*path)
	{
		err_system_call("malloc");
		child_minishell_exit(mini, NULL, argv, \
			SYSTEMCALL_EXITSTATUS);
	}
}

void	set_path_buffer(char *path_buffer, char *path_env, \
	char *cmd, char **chr)
{
	*chr = ft_strchr(path_env + 1, ':');
	if (!*chr)
		ft_strlcpy(path_buffer, path_env, PATH_MAX);
	else if (*chr - path_env == 1)
		ft_strlcpy(path_buffer, ".", PATH_MAX);
	else
		ft_strlcpy(path_buffer, path_env, *chr - path_env + 1);
	ft_strlcat(path_buffer, "/", PATH_MAX);
	ft_strlcat(path_buffer, cmd, PATH_MAX);
}

void	get_path_from_env(char **path, char **argv, \
	t_mini *mini, char *path_env)
{
	char	path_buffer[PATH_MAX];
	char	*chr;

	while (1)
	{
		set_path_buffer(path_buffer, path_env, \
			argv[0], &chr);
		if (!access(path_buffer, F_OK))
			break ;
		if (!chr)
			child_minishell_exit(mini, err_cmd_not_found, \
			argv, NOT_FOUND_ERR);
		path_env = chr + 1;
	}
	if (access(path_buffer, X_OK))
		child_minishell_exit(mini, err_permission, \
			argv, PERMISSION_ERR);
	*path = ft_strdup(path_buffer);
	if (!*path)
	{
		err_system_call("malloc");
		child_minishell_exit(mini, NULL, argv, \
			SYSTEMCALL_EXITSTATUS);
	}
}

// it don't check if it is correct dir or not.
// used only inside child process
void	get_path(char **path, t_mini *mini, char **argv)
{
	char	*path_env;

	if (PATH_MAX < 1024)
		return ;
	path_env = normal_getenv("PATH", mini);
	if (!path_env || !*path_env)
		get_cwd_path(path, argv, mini);
	else
		get_path_from_env(path, argv, mini, path_env);
}

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

void	check_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		fprintf(stderr, "%s\n", argv[i]);
		i++;
	}
}

void	check_word(t_word *word)
{
	while (word)
	{
		fprintf(stderr, "%s ", word->word);
		word = word->next;
	}
	fprintf(stderr, "\n");
}

void	exec_child_proc(t_mini *mini, t_node *node)
{
	char	**argv;
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	if (expand_word(node, mini))
		systemcall_minishell_exit(mini, "malloc");
	// check_word(node->word);
	if (store_argv(node, &argv))
		systemcall_minishell_exit(mini, "malloc");
	// check_argv(argv);
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
	waitpid(cmd_id, &status, 0);
	if (WEXITSTATUS(status) == SYSTEMCALL_EXITSTATUS)
		systemcall_minishell_exit(mini, NULL);
	store_status(WEXITSTATUS(status), mini);
}
