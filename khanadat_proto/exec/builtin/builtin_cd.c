/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:45 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/06 14:22:43 by khanadat         ###   ########.fr       */
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
	if (chdir(dir) < 0)
	{
		err_cd(dir);
		store_status(FAILURE, mini);
		return ;
	}
	if (update_pwd(mini))
		systemcall_minishell_exit(mini, "malloc");
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
		return (ERR);
	if (set_mini_envp(ENV_PWD, pwd, &mini->envp[i]))
		return (free(pwd), ERR);
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
	return (true);
}
