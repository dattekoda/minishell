/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 17:55:32 by khanadat         ###   ########.fr       */
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

void	get_cwd_path(char **path, char *cmd)
{
	char	path_buffer[PATH_MAX];

	ft_strlcpy(path_buffer, "./", PATH_MAX);
	ft_strlcat(path_buffer, cmd, PATH_MAX);
	if (access(path_buffer, F_OK))
		exit((err_cmd_not_found(cmd), NOT_FOUND_ERR));
	if (access(path_buffer, X_OK))
		exit((err_permission(cmd), PERMISSION_ERR));
	*path = ft_strdup(path_buffer);
	if (!*path)
		exit((err_system_call("malloc"), \
		SYSTEMCALL_EXITSTATUS));
}

void	get_path_from_env(char **path, char *cmd, char *path_env)
{
	char	path_buffer[PATH_MAX];
	char	*chr;

	while (1)
	{
		chr = ft_strchr(path_env + 1, ':');
		if (!chr)
			ft_strlcpy(path_buffer, path_env, PATH_MAX);
		else if (chr - path_env == 1)
			ft_strlcpy(path_buffer, ".", PATH_MAX);
		else
			ft_strlcpy(path_buffer, path_env, chr - path_env + 1);
		ft_strlcat(path_buffer, "/", PATH_MAX);
		ft_strlcat(path_buffer, cmd, PATH_MAX);
		if (!access(path_buffer, F_OK))
			break ;
		if (!chr)
			exit((err_cmd_not_found(cmd), NOT_FOUND_ERR));
		path_env = chr + 1;
	}
	if (access(path_buffer, X_OK))
		exit((err_permission(cmd), PERMISSION_ERR));
	*path = ft_strdup(path_buffer);
	if (!*path)
		exit((err_system_call("malloc"), SYSTEMCALL_EXITSTATUS));
}

// it don't check if it is correct dir or not.
// used only inside child process
void	get_path(char **path, t_mini *mini, char *cmd)
{
	char	*path_env;

	if (PATH_MAX < 1024)
		return ;
	path_env = mini_getenv("PATH", mini);
	if (!path_env || !*path_env)
		get_cwd_path(path, cmd);
	else
		get_path_from_env(path, cmd, path_env);
}

// void	expand_word(t_mini *mini, t_node *node)
// {
// 	while ()
// }

void	exec_child_proc(t_mini *mini, t_node *node)
{
	char	*path;

	// expand_word(mini, node);
	get_path(&path, mini, node->word->word);
	printf("%s\n", path);
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
	mini->status = WEXITSTATUS(status);
}