/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:37:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"

#include "libft.h"

static size_t	need_new_line(char **argv);

void	exec_echo(t_mini *mini, char **argv)
{
	size_t	i;
	bool	print_new_line;

	i = need_new_line(argv);
	print_new_line = (i == 1);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (print_new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	store_status(SUCCESS, mini);
}

static size_t	need_new_line(char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	i++;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j++] != '-')
			break ;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j])
			break ;
		i++;
	}
	return (i);
}
