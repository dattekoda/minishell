/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:46:11 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 20:27:03 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"

static bool	is_valid_exit_arg(char *str, int64_t *num);

void	exec_exit(t_mini *mini, char **argv)
{
	int64_t	status;

	if (!mini->is_pipe)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		status = SUCCESS;
	else if (!is_valid_exit_arg(argv[1], &status))
	{
		err_exit_numeric(argv[1]);
		store_status(SYNTAX_ERR, mini);
		return ;
	}
	store_status((int)status, mini);
	if (argv[1] && argv[2])
	{
		err_too_many("exit");
		store_status(SYNTAX_ERR, mini);
		return ;
	}
	normal_minishell_exit(mini, NULL, NULL, (int)ft_atoi(mini->status));
}

static bool	is_valid_exit_arg(char *str, int64_t *num)
{
	bool		issigned;
	int64_t	unum;
	int64_t	old_unum;

	unum = 0;
	issigned = false;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (false);
	if (*str == '-' || *str == '+')
		issigned = (*str++ == '-');
	if (!*str)
		return (false);
	while (ft_isdigit(*str))
	{
		old_unum = unum;
		unum = 10 * unum + (*str - '0');
		if (unum < old_unum)
			break ;
		str++;
	}
	*num = (1 - 2 * issigned) * unum;
	if (*str && !ft_isspace(*str))
		return (false);
	return (true);
}
