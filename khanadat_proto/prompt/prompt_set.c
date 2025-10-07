/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:38:47 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/06 00:14:16 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "libft.h"
#include "status.h"
#include "tokenizer.h"
#include "ast.h"

static int	set_envp(t_mini *mini, char *envp[]);
static int	set_prompt(t_mini *mini);

int	set_minishell(t_mini *mini, char *envp[])
{
	ft_bzero(mini, sizeof(t_mini));
	store_status(0, mini);
	if (set_envp(mini, envp))
		return (ERR);
	if (set_prompt(mini))
		return (ERR);
	return (SUCCESS);
}

// set node and free line
int	set_node(t_mini *mini)
{
	int		status;
	t_token	*token;

	status = get_token(&token, mini->line);
	if (status < 0)
		systemcall_minishell_exit(mini, NULL);
	if (status == SYNTAX_ERR)
		return (PROMPT_CONTINUE);
	status = get_node(&(mini->node), token);
	if (status < 0)
		systemcall_minishell_exit \
		((free_token(&token), mini), NULL);
	if (status == SYNTAX_ERR)
		return (free_token(&token), \
			PROMPT_CONTINUE);
	return (free_token(&token), \
		mini_safe_free((void **)&(mini->line)), \
		SUCCESS);
}

static int	set_envp(t_mini *mini, char *envp[])
{
	size_t	i;

	while (envp[mini->envp_len])
		(mini->envp_len)++;
	mini->envp_size = (mini->envp_len) * 2;
	mini->envp = ft_calloc(mini->envp_size + 1, sizeof(char *));
	if (!mini->envp)
		return (err_system_call("malloc"), ERR);
	i = 0;
	while (i < mini->envp_len)
	{
		mini->envp[i] = ft_strdup(envp[i]);
		if (!mini->envp[i])
		{
			while (i--)
				free(mini->envp[i]);
			return (free(mini->envp), err_system_call("malloc"), ERR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	set_prompt(t_mini *mini)
{
	mini->prompt = ft_strjoin \
	(access_program_name(NULL), "$ ");
	if (!mini->prompt)
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}
