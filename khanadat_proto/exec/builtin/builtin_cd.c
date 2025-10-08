/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:19:45 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 08:14:53 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "status.h"
#include "libft.h"

static bool	is_valid_cd(t_mini *mini, char **argv, char *dir);
static void	cd_upper(t_mini *mini);

void	exec_cd(t_mini *mini, char **argv)
{
	char	*dir;

	if (!argv[1])
		dir = normal_getenv("HOME", mini);
	else
		dir = argv[1];
	if (!is_valid_cd(mini, argv, dir))
		return ;
	if (!ft_strcmp("..", dir))
	{
		cd_upper(mini);
		return ;
	}
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

static void	cd_upper(t_mini *mini)
{
	int		status;
	char	*tmp;

	tmp = NULL;
	if (mini->mini_pwd)
		tmp = ft_strrchr(mini->mini_pwd, '/');
	if (!tmp)
	{
		err_cd("..");
		store_status(FAILURE, mini);
		return ;
	}
	*tmp = '\0';
	status = chdir(mini->mini_pwd);
	*tmp = '/';
	if (status < 0)
	{
		err_cd("..");
		store_status(FAILURE, mini);
		return ;
	}
	if (update_pwd(mini))
		systemcall_minishell_exit(mini, "malloc");
	store_status(SUCCESS, mini);
}
