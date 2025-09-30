/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_word_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:03:48 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:37:50 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include "minishell_define.h"
#include "expand_define.h"
#include "libft.h"

// need add t_word then true
// else return false
bool	need_split(t_dollar **dol, size_t *len)
{
	size_t	i;

	while (*len == 0 && ft_isspace(*((*dol)->value)))
		(*dol)->value = (*dol)->value + 1;
	i = 0;
	while ((*dol)->value[i] && !ft_isspace((*dol)->value[i]))
		i++;
	*len += i;
	if ((*dol)->value[i] == '\0')
		return (false);
	return (true);
}

size_t	count_word_len(t_dollar **dol)
{
	size_t	len;

	len = 0;
	while ((*dol))
	{
		if ((*dol)->wkind == WD_DOLLAR \
		&& need_split(dol, &len))
			return (len);
		else if ((*dol)->wkind != WD_DOLLAR)
			len += (*dol)->value_len;
		(*dol) = (*dol)->next;
	}
	return (len);
}

void	set_word_word(t_word *new_word, t_dollar *dol_tail)
{
	size_t		i;

	i = 0;
	while (dol_tail)
	{
		if (dol_tail->wkind == WD_DOLLAR)
		{
			ft_strlcat(new_word->word, dol_tail->value, new_word->word_len + 1);
			while (*dol_tail->value && !ft_isspace(*(dol_tail->value)))
				(dol_tail->value) = (i++, dol_tail->value + 1);
			if (new_word->word[new_word->word_len - 1])
				break ;
		}
		else
		{
			ft_memmove(new_word->word + i, \
				dol_tail->value, dol_tail->value_len);
			i += dol_tail->value_len;
		}
		dol_tail = dol_tail->next;
	}
}
