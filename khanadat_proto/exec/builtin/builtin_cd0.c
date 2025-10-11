/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:45 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/11 19:26:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "builtin_cd_utils.h"
#include "libft.h"

static bool	not_valid_cd(t_mini *mini, char **argv, char *dir);
static void	cd_parent_dir(t_mini *mini, char *old_pwd);
static void	update_oldpwd(t_mini *mini, char *old_pwd);
static void	update_success_cd(t_mini *mini, char *old_pwd);

void	exec_cd(t_mini *mini, char **argv)
{
	char	*dir;
	char	*old_pwd;

	if (!argv[1])
		dir = normal_getenv("HOME", mini);
	else
		dir = argv[1];
	if (not_valid_cd(mini, argv, dir))
		return ;
	old_pwd = mini_getcwd();
	if (!ft_strcmp("..", dir))
	{
		cd_parent_dir(mini, old_pwd);
		return ;
	}
	if (chdir(dir) < 0)
	{
		free(old_pwd);
		err_cd(dir);
		store_status(FAILURE, mini);
		return ;
	}
	update_success_cd(mini, old_pwd);
}

static bool	not_valid_cd(t_mini *mini, char **argv, char *dir)
{
	if (!dir)
		return (err_no_home("cd"), \
		store_status(FAILURE, mini), true);
	if (argv[1] && argv[2])
		return (err_too_many("cd"), \
		store_status(SYNTAX_ERR, mini), true);
	return (false);
}

static void	cd_parent_dir(t_mini *mini, char *old_pwd)
{
	if (!chdir(".."))
	{
		update_success_cd(mini, old_pwd);
		return ;
	}
	if (chdir_parent(mini))
	{
		free(old_pwd);
		store_status(FAILURE, mini);
		return ;
	}
	store_status(SUCCESS, mini);
	update_pwd(mini);
}

static void	update_oldpwd(t_mini *mini, char *old_pwd)
{
	size_t	i;

	if (!old_pwd)
		return ;
	i = search_envp_i(mini, ENV_OLDPWD, ENV_OLDPWD_LEN);
	if (!mini->envp[i])
	{
		free(old_pwd);
		return ;
	}
	if (set_mini_envp(ENV_OLDPWD, old_pwd, &mini->envp[i]))
	{
		free(old_pwd);
		systemcall_minishell_exit(mini, "malloc");
		return ;
	}
	free(old_pwd);
	return ;
}

static void	update_success_cd(t_mini *mini, char *old_pwd)
{
	update_oldpwd(mini, old_pwd);
	update_pwd(mini);
	store_status(SUCCESS, mini);
}
