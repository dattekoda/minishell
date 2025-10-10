/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:35:22 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/10 08:55:40 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "libft.h"

void	exec_pwd(t_mini *mini)
{
	char	*cwd;

	cwd = mini_getcwd();
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		store_status(0, mini);
		return ;
	}
	if (!cwd)
		cwd = normal_getenv("PWD", mini);
	if (!cwd)
		cwd = mini->mini_pwd;
	if (!cwd)
	{
		err_pwd();
		store_status(FAILURE, mini);
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	store_status(SUCCESS, mini);
}
