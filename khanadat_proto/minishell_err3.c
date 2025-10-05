/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:59:55 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 17:22:35 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_lib.h"
#include "libft.h"

void	err_msg_env(char *file)
{
	ft_putstr_fd(access_program_name(NULL), STDERR_FILENO);
	ft_putstr_fd(": cd: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": Options and arguments" \
		" are not supported", STDERR_FILENO);
}

void	err_export(char *file)
{
	ft_putstr_fd(access_program_name(NULL), STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	err_exit_numeric(char *file)
{
	ft_putstr_fd(access_program_name(NULL), STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}
