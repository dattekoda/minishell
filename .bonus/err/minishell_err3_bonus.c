/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err3_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:59:55 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "libft.h"

void	err_msg_env(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": env: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": Options and arguments" \
		" are not supported", STDERR_FILENO);
}

void	err_export(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": export: `", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	err_exit_numeric(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

// void	err_sig_msg(t_mini *mini)
// {
// 	if (!ft_strcmp(mini->status, "131"))
// 	{
// 		ft_putstr_fd("Quit: ", STDERR_FILENO);
// 		ft_putnbr_fd(3, STDERR_FILENO);
// 		ft_putchar_fd('\n', STDERR_FILENO);
// 	}
// 	if (!ft_strcmp(mini->status, "130"))
// 		ft_putchar_fd('\n', STDERR_FILENO);
// }
