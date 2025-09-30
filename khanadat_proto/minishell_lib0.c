/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:15:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/01 01:27:07 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
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

void	safe_minishell_free(t_mini *mini)
{
	free_split(mini->envp);
	mini_safe_free((void **)&mini->line);
	free_node(&mini->node);
	rl_clear_history();
}

void	noline_minishell_exit(t_mini *mini)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	safe_minishell_free(mini);
	exit(SUCCESS);
}

void	systemcall_minishell_exit(t_mini *mini, char *func)
{
	if (func)
		err_system_call(func);
	safe_minishell_free(mini);
	exit(SYSTEMCALL_EXITSTATUS);
}

void	child_minishell_exit(t_mini *mini, void func(char *), \
	char **argv, int status)
{
	if (func)
		func(argv[0]);
	free(argv);
	safe_minishell_free(mini);
	exit(status);
}
