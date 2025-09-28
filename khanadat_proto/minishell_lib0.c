/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:15:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 11:02:24 by khanadat         ###   ########.fr       */
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

// free(*@join) and joined first and buffer
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
	safe_free((void **)&mini->line);
	free_node(&mini->node);
	rl_clear_history();
	free_program_name();
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

char	*mini_getenv(char *var, t_mini *mini)
{
	size_t	i;
	size_t	len;
	char	*chr;

	i = 0;
	while (i < mini->envp_len)
	{
		len = ft_strlen(var);
		if (!ft_strncmp(var, mini->envp[i], len) \
		&& mini->envp[i][len] == '=')
			break ;
		i++;
	}
	if (!mini->envp[i])
		return (NULL);
	chr = ft_strchr(mini->envp[i], '=');
	if (chr)
		return (chr + 1);
	return (NULL);
}
