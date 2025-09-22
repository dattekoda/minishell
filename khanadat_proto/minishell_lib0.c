/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:15:10 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 08:52:20 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "status.h"
#include "minishell_err.h"
#include "libft.h"
#include "minishell_define.h"
#include "tokenizer.h"
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

void	free_minienvp(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (i < mini->envp_count)
	{
		if (mini->envp[i])
			free(mini->envp[i]);
		mini->envp[i++] = NULL;
	}
	if (mini->envp)
		free(mini->envp);
	mini->envp = NULL;
}

void	safe_minishell_exit(t_mini *mini)
{
	if (mini->node)
		free_node(mini->node);
	if (mini->envp)
		free_minienvp(mini);
	free(mini);
	mini = NULL;
	rl_clear_history();
	exit(SYSTEMCALL_EXITSTATUS);
}

char	*mini_getenv(char *var, t_mini *mini)
{
	size_t	i;
	size_t	len;
	char	*chr;

	i = 0;
	while (i < mini->envp_count)
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
