/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_utils1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 01:26:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_define_bonus.h"
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "classify_utils_bonus.h"
#include "libft.h"

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
		return (add_status(cur, mini, word, true));
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->orig = (*word - 1);
	new->is_quoted = true;
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
	while (**word && !ft_strchr(OUTSIDE_DELIMITER, **word))
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}
