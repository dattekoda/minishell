/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:37:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 18:49:07 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"

static bool	new_line_checker(char *arg);

void	exec_echo(t_mini *mini, char **argv)
{
	size_t	i;
	bool	print_new_line;

	print_new_line = new_line_checker(argv[1]);
	i = !print_new_line;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	store_status(SUCCESS, mini);
}

static bool	new_line_checker(char *arg)
{
	if (!arg)
		return (true);
	if (!*arg)
		return (true);
	if (*arg++ != '-')
		return (true);
	if (*arg != 'n')
		return (true);
	while (*arg && *arg == 'n')
		arg++;
	if (!*arg)
		return (false);
	return (true);
}
