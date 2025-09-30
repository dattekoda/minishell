/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:57:38 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 13:58:47 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_utils.h"
#include "expand_define.h"
#include "libft.h"

// set the second arg, **word be '$' mark
// skip word and get expanded value
// return stack char *.
// if couldn't find any value then
// set value as "\0"
t_dollar	*add_dollar(t_dollar *cur, t_mini *mini, \
	char **word, t_WordKind kind)
{
	char		*value;
	t_dollar	*new;

	(*word)++;
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = kind;
	if (**word == '?')
	{
		new->value = mini->status;
		new->value_len = ft_strlen(new->value);
		return ((*word)++, new);
	}
	value = mini_getenv(word, mini);
	if (!value)
		new->value = &(mini->status[3]);
	else
		new->value = value;
	new->value_len = ft_strlen(new->value);
	return (new);
}

t_dollar	*add_single(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->value = *word + 1;
	new->wkind = WD_SINGLE;
	*word = ft_strchr(new->value, '\'') + 1;
	new->value_len = (size_t)(*word - 1 - new->value);
	return (new);
}

t_dollar	*add_double(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = WD_DOUBLE;
	new->value = *word + (**word == '\"');
	new->wkind = WD_DOUBLE;
	while (**word && **word != '\"' \
	&& **word != '$')
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}

t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp)
{
	(*tmp)++;
	while (**tmp && **tmp != '\"' && *cur)
	{
		if (**tmp == '$')
		{
			*cur = add_dollar(*cur, mini, tmp, WD_DDOLLAR);
			continue ;
		}
		*cur = add_double(*cur, tmp);
	}
	if (**tmp == '\"')
		(*tmp)++;
	return (*cur);
}

t_dollar	*add_outside(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = WD_OUTSIDE;
	new->value = *word;
	while (**word && !ft_strchr("\'\"$", **word))
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}
