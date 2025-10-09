/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:32:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 09:34:02 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_lib.h"
#include "libft.h"

void	err_cd(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	perror(file);
}

void	err_cd_getcwd(void)
{
	ft_putstr_fd("cd: error retrieving current directory", STDERR_FILENO);
	ft_putstr_fd(": getcwd: cannot access parent directories", STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
}

void	err_no_home(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": Home not set", STDERR_FILENO);
}

void	err_too_many(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
}

void	err_pwd(void)
{
	ft_putstr_fd("pwd: error retrieving current directorory: ", STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
}

// void	err_not_dir(char *file)
// {
// 	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
// 	ft_putstr_fd(": cd: ", STDERR_FILENO);
// 	ft_putstr_fd(file, STDERR_FILENO);
// 	ft_putendl_fd(": Not a directory", STDERR_FILENO);
// }

// void	err_cd_permission(char *file)
// {
// 	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
// 	ft_putstr_fd(": cd: ", STDERR_FILENO);
// 	ft_putstr_fd(file, STDERR_FILENO);
// 	ft_putendl_fd(": Permission denied", STDERR_FILENO);
// }
