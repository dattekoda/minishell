/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iokuno <iokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:26:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 22:20:36 by iokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classify_utils.h"
#include "expand_define.h"
#include "libft.h"
#include "minishell_define.h"
#include "minishell_utils.h"

static t_dollar	*add_d_dollar(t_dollar *cur, t_mini *mini, char **word);
static t_dollar	*add_double(t_dollar *cur, char **word);

// no need if ((**tmp) == '\"')?
t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp)
{
	(*tmp)++;
	while (**tmp && *cur)
	{
		if (**tmp == '$')
			*cur = add_d_dollar(*cur, mini, tmp);
		else
			*cur = add_double(*cur, tmp);
		if (**tmp == '\"')
			break ;
	}
	(*tmp)++;
	return (*cur);
}

// dollar expansion inside double quote
static t_dollar	*add_d_dollar(t_dollar *cur, t_mini *mini, char **word)
{
	t_dollar	*new;

	(*word)++;
	if (**word == '?')
		return (add_status(cur, mini, word));
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->value = mini_getenv(word, mini);
	new->value_len = ft_strlen(new->value);
	return (new);
}

// normally inside double quote
static t_dollar	*add_double(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->value = *word;
	new->is_quoted = true;
	while (**word && **word != '\"' && **word != '$')
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
