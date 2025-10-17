/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:15:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/17 16:03:30 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_utils.h"
#include "libft.h"
#include "ast.h"

// free join and joined first and buffer
// if malloc failed, put error
int	safe_join(char **joined, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(*joined, buffer);
	free(*joined);
	if (!tmp)
		return (err_system_call("malloc"), ERR);
	*joined = tmp;
	return (SUCCESS);
}

void	minishell_exit(t_mini *mini)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	t_mini_free(mini);
	exit(SUCCESS);
}

void	failure_minishell_exit(t_mini *mini, \
	void (*func)(char *), char *file, int status)
{
	(*func)(file);
	t_mini_free(mini);
	exit(status);
}

void	systemcall_minishell_exit(t_mini *mini, char *func)
{
	mini->is_sys_err = true;
	if (func)
		err_system_call(func);
	t_mini_free(mini);
	exit(SYSTEMCALL_EXITSTATUS);
}
