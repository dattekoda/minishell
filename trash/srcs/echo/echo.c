/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:49:21 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/10 02:16:19 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int	builtin_echo(int argc, char *argv[])
{
	int		i;
	bool	first;
	bool	no_nl;

	no_nl = false;
	if (argc != 1)
	{
		no_nl = (strcmp(argv[1], "-n") == 0);
		i = (no_nl); // no_nl==true then 1 else 0
		first = true;
		while (++i < argc)
		{
			if (!first)
				ft_putchar_fd(' ', STDOUT_FILENO);
			first = false;
			ft_putstr_fd(argv[i], STDOUT_FILENO);
		}
	}
	if (!no_nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	builtin_echo(argc, argv);
// }
