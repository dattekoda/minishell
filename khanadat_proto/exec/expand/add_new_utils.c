/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dollar_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:03:48 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:37:50 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "expand_define.h"
#include "libft.h"
#include "minishell_define.h"

void	set_new_str(char *str, t_dollar *dol_tail)
{
	size_t	i;

	i = 0;
	while (dol_tail && dol_tail->dkind != WD_SPACE)
	{
		ft_memmove(str + i, dol_tail->value, dol_tail->value_len);
		i += dol_tail->value_len;
		dol_tail = dol_tail->next;
	}
}

bool	is_quoted(t_dollar *dol)
{
	while (dol)
	{
		if (dol->is_quoted)
			return (true);
		dol = dol->next;
	}
	return (false);
}

size_t	count_word_len(t_dollar **dol)
{
	size_t	len;

	len = 0;
	while ((*dol))
	{
		if ((*dol)->dkind == WD_SPACE)
		{
			(*dol) = (*dol)->next;
			return (len);
		}
		len += (*dol)->value_len;
		(*dol) = (*dol)->next;
	}
	return (len);
}
