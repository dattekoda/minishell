/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:26:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/02 21:34:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_define.h"
#include "minishell_define.h"
#include "classify_utils.h"
#include "libft.h"

static t_dollar	*add_d_dollar(t_dollar *cur, t_mini *mini, char **word);
static t_dollar	*add_double(t_dollar *cur, char **word);

// no need if ((**tmp) == '\"')?
t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp)
{
	(*tmp)++;
	while (**tmp && **tmp != '\"' && *cur)
	{
		if (**tmp == '$')
		{
			*cur = add_d_dollar(*cur, mini, tmp);
			continue ;
		}
		*cur = add_double(*cur, tmp);
	}
	if (**tmp == '\"')
		(*tmp)++;
	return (*cur);
}

static t_dollar	*add_d_dollar(t_dollar *cur, t_mini *mini, char **word)
{
	t_dollar	*new;
	char		*value;

	(*word)++;
	if (**word == '?')
		return (add_status(cur, mini, word));
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	value = mini_getenv(word, mini);
	if (!value)
		new->value = &mini->status[3];
	else
		new->value = value;
	new->value_len = ft_strlen(new->value);
	return (new);
}

static t_dollar	*add_double(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->value = *word + (**word == '\"');
	while (**word && **word != '\"' \
	&& **word != '$')
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}

t_dollar	*add_outside(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->value = *word;
	while (**word && !ft_strchr("\'\"$", **word))
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}

// found var then return value
// else return NULL
// push forward var
char	*mini_getenv(char **var, t_mini *mini)
{
	size_t	len;
	size_t	i;
	char	*chr;

	i = 0;
	chr = *var;
	while (**var && !ft_strchr("\'\"$", **var))
		(*var)++;
	if (*var == chr)
		return (&mini->status[4]);
	len = *var - chr;
	while (i < mini->envp_len)
	{
		if (!ft_strncmp(chr, mini->envp[i], len) \
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
