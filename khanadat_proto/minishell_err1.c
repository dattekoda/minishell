/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:13:47 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 19:22:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "minishell_lib.h"
#include "minishell_define.h"

void	err_file(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(file);
}

void	err_is_dir(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
}

// void	err_file(char *file)
// {
// 	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(file, STDERR_FILENO);
// 	ft_putendl_fd(": permission denied", STDERR_FILENO);
// }

// void	err_file(char *file)
// {
// 	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(file, STDERR_FILENO);
// 	ft_putendl_fd(": no such file or directory", STDERR_FILENO);
// }

void	err_heredoc(char *file)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": warning: here-document at line 1 "\
		"delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	err_ambiguous(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}
