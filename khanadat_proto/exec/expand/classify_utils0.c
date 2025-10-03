/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:57:38 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 13:58:47 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_utils.h"
#include "expand_define.h"
#include "minishell_lib.h"
#include "classify_utils.h"
#include "libft.h"

static t_dollar	*add_space(t_dollar *cur, char **value);
static t_dollar	*add_dollar(t_dollar *cur, char **value);

t_dollar	*classify_more_dollar(t_dollar **cur, t_mini *mini, char **tmp)
{
	char	*value;

	(*tmp)++;
	if (**tmp == '?')
		return (add_status(*cur, mini, tmp));
	value = mini_getenv(tmp, mini);
	// if (!value)
	// 	value = &mini->status[3];
	while (*value && *cur)
	{
		if (ft_isspace(*value))
		{
			*cur = add_space(*cur, &value);
			continue ;
		}
		*cur = add_dollar(*cur, &value);
	}
	return (*cur);
}

// if space token come, then add new t_word
static t_dollar	*add_space(t_dollar *cur, char **value)
{
	t_dollar	*new;

	while (**value && ft_isspace(**value))
		(*value)++;
	if (cur->dkind == WD_HEAD)
		return (cur);
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_SPACE;
	return (new);
}

static t_dollar	*add_dollar(t_dollar *cur, char **value)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->value = *value;
	new->dkind = WD_WORD;
	while (**value && !ft_isspace(**value))
	{
		new->value_len++;
		(*value)++;
	}
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
	new->dkind = WD_WORD;
	*word = ft_strchr(new->value, '\'') + 1;
	new->value_len = (size_t)(*word - 1 - new->value);
	return (new);
}

t_dollar	*add_status(t_dollar *cur, t_mini *mini, char **word)
{
	t_dollar	*new;

	new = ft_calloc(sizeof(t_dollar), 1);
	if (!new)
		return (NULL);
	cur->next = new;
	new->dkind = WD_WORD;
	new->value = mini->status;
	(*word)++;
	new->value_len = ft_strlen(new->value);
	return (new);
}
