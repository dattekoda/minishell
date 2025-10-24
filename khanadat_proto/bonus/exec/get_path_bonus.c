/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:20:01 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"
#include <sys/stat.h>
#include <unistd.h>

void	get_cwd_path(char **path, char **argv, t_mini *mini)
{
	char	path_buffer[PATH_MAX];

	ft_strlcpy(path_buffer, "./", PATH_MAX);
	ft_strlcat(path_buffer, argv[0], PATH_MAX);
	if (access(path_buffer, F_OK))
		failure_minishell_exit(mini, &err_file, \
		argv[0], NOT_FOUND_ERR);
	if (access(path_buffer, X_OK))
		failure_minishell_exit(mini, &err_file, \
		argv[0], PERMISSION_ERR);
	*path = ft_strdup(path_buffer);
	if (!*path)
	{
		err_system_call("malloc");
		failure_minishell_exit(mini, NULL, argv[0], \
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
			failure_minishell_exit(mini, &err_cmd_not_found, \
			argv[0], NOT_FOUND_ERR);
		path_env = chr + 1;
	}
	if (access(path_buffer, X_OK))
		failure_minishell_exit(mini, &err_file, \
			argv[0], PERMISSION_ERR);
	*path = ft_strdup(path_buffer);
	if (!*path)
		systemcall_minishell_exit(mini, "malloc");
}

void	get_abs_path(char **path, char **argv, t_mini *mini)
{
	if (access(argv[0], F_OK))
		failure_minishell_exit(mini, &err_cmd_not_found, \
			argv[0], NOT_FOUND_ERR);
	if (mini_is_dir(argv[0]))
		failure_minishell_exit(mini, &err_is_dir, \
		argv[0], IS_DIR_ERR);
	if (access(argv[0], X_OK))
		failure_minishell_exit(mini, &err_file, \
			argv[0], PERMISSION_ERR);
	*path = argv[0];
}

// it don't check if it is correct dir or not.
// used only inside child process
// hard coding 1024 to avoid segmentation fault
void	get_path(char **path, t_mini *mini, char **argv)
{
	char	*path_env;

	if (PATH_MAX < 1024)
		return ;
	if (!argv[0][0])
		failure_minishell_exit(mini, &err_cmd_not_found, \
			"\'\'", NOT_FOUND_ERR);
	if (ft_strchr(argv[0], '/'))
	{
		get_abs_path(path, argv, mini);
		return ;
	}
	path_env = normal_getenv("PATH", mini);
	if (!path_env || !*path_env)
		get_cwd_path(path, argv, mini);
	else
		get_path_from_env(path, argv, mini, path_env);
}
