/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:46:11 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/13 19:43:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_utils.h"

#include "libft.h"

static bool	is_valid_exit_arg(char *str, int64_t *num);

void	exec_exit(t_mini *mini, char **argv)
{
	int64_t	status;

	status = SUCCESS;
	if (!mini->is_pipe && !mini->is_inside)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argv[1] && argv[2])
	{
		err_too_many("exit");
		store_status(SYNTAX_ERR, mini);
		return ;
	}
	if (argv[1] && !is_valid_exit_arg(argv[1], &status))
	{
		err_exit_numeric(argv[1]);
		store_status(SYNTAX_ERR, mini);
		return ;
	}
	if (!status)
		status = (int64_t)ft_atoi(mini->status);
	normal_minishell_exit(mini, NULL, NULL, (int)status);
}

static bool	is_valid_exit_arg(char *str, int64_t *num)
{
	bool		issigned;
	int64_t		old_num;

	*num = 0;
	issigned = false;
	while (ft_isspace(*str))
		str++;
	if (!*str)
		return (false);
	if (*str == '-' || *str == '+')
		issigned = (*str++ == '-');
	if (!*str || ft_isspace(*str))
		return (false);
	while (ft_isdigit(*str))
	{
		old_num = *num;
		*num = 10 * *num + (*str - '0');
		if (*num < old_num)
			break ;
		str++;
	}
	*num *= (1 - 2 * issigned);
	if (*str && !ft_isspace(*str))
		return (false);
	return (true);
}
