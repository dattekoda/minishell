/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:38:47 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 20:25:42 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define.h"
#include "minishell_utils.h"
#include "minishell_err.h"
#include "libft.h"
#include "tokenizer.h"
#include "ast.h"
#include <stdlib.h>

static int	set_envp(t_mini *mini, char *envp[]);
static int	set_prompt(t_mini *mini);

int	set_minishell(t_mini *mini, char *envp[])
{
	ft_bzero(mini, sizeof(t_mini));
	store_status(SUCCESS, mini);
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
		return (store_status(SYNTAX_ERR, mini), \
				PROMPT_CONTINUE);
	status = get_node(&(mini->node), token);
	if (status < 0)
		systemcall_minishell_exit \
		((free_token(&token), mini), NULL);
	if (status == PROMPT_CONTINUE)
		return (free_token(&token), PROMPT_CONTINUE);
	if (status == SYNTAX_ERR)
		return (free_token(&token), \
			store_status(SYNTAX_ERR, mini), \
			PROMPT_CONTINUE);
	return (free_token(&token), \
		SUCCESS);
}

static void	update_shlvl(t_mini *mini)
{
	size_t	i;
	int		num;
	char	*shlvl_val;

	normal_getenv("SHLVL", mini);
	i = search_envp_i(mini, "SHLVL", SHLVL_LEN);
	if (!mini->envp[i])
	{
		if (add_mini_len(mini))
			systemcall_minishell_exit(mini, "malloc");
		set_mini_envp("SHLVL", "1", &mini->envp[i]);
		return ;
	}
	
	num = ft_atoi(ft_strchr(mini->envp[i], '=') + 1);
	shlvl_val = ft_itoa(num + 1);
	set_mini_envp("SHLVL", shlvl_val, &mini->envp[i]);
	free(shlvl_val);
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
	update_pwd(mini);
	update_shlvl(mini);
	return (SUCCESS);
}

static int	set_prompt(t_mini *mini)
{
	mini->prompt = ft_strdup("$ ");
	if (!mini->prompt)
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}
