/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:45 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 23:44:42 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "status.h"
#include "libft.h"

#define ENV_PWD "PWD"
#define ENV_PWD_LEN 3

static int	update_pwd(t_mini *mini);
static int	set_mini_envp(char *var, char *val, char **envp_i);
static bool	is_valid_cd(t_mini *mini, char **argv, char *dir);

void	exec_cd(t_mini *mini, char **argv)
{
	char	*dir;

	if (!argv[1])
		dir = normal_getenv("HOME", mini);
	else
		dir = argv[1];
	if (!is_valid_cd(mini, argv, dir))
		return ;
	if (chdir(dir))
		perror("chdir");
	if (update_pwd(mini))
		normal_minishell_exit(mini, &free, \
			argv, SYSTEMCALL_EXITSTATUS);
	store_status(SUCCESS, mini);
}

static int	update_pwd(t_mini *mini)
{
	size_t	i;
	char	*pwd;

	i = search_envp_i(mini, ENV_PWD, ENV_PWD_LEN);
	if (!mini->envp[i])
		return (SUCCESS);
	pwd = mini_getcwd();
	if (!pwd)
		return (err_system_call("malloc"), ERR);
	if (set_mini_envp(ENV_PWD, pwd, &mini->envp[i]))
		return (free(pwd), err_system_call("malloc"), ERR);
	return (free(pwd), SUCCESS);
}

static int	set_mini_envp(char *var, char *val, char **envp_i)
{
	size_t	len;
	size_t	i;
	size_t	var_len;
	size_t	val_len;

	if (*envp_i)
		free(*envp_i);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	len = var_len + 1 + val_len;
	*envp_i = ft_calloc(len + 1, sizeof(char));
	if (!*envp_i)
		return (ERR);
	i = 0;
	ft_memmove(*envp_i, var, var_len);
	i += var_len;
	ft_memmove(*envp_i + i, "=", 1);
	i += 1;
	ft_memmove(*envp_i + i, val, val_len);
	return (SUCCESS);
}

static bool	is_valid_cd(t_mini *mini, char **argv, char *dir)
{
	if (!dir)
		return (err_no_home("cd"), \
		store_status(FAILURE, mini), false);
	if (argv[1] && argv[2])
		return (err_too_many("cd"), \
		store_status(SYNTAX_ERR, mini), false);
	if (access(dir, F_OK))
		return (err_cd(argv[1]), \
		store_status(FAILURE, mini), false);
	if (!mini_is_dir(dir))
		return (err_not_dir(argv[1]), \
		store_status(FAILURE, mini), false);
	if (access(dir, X_OK))
		return (err_cd_permission(argv[1]), \
		store_status(FAILURE, mini), false);
	return (true);
}
