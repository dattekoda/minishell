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

#include <stddef.h>
#include <stdbool.h>
#include "minishell_define.h"
#include "expand_define.h"
#include "libft.h"

static bool	check_first_space(t_dollar **dol, size_t *len);
static bool	need_split(t_dollar **dol, size_t *len);

#include <stdio.h>
void	set_new_str(char *str, t_dollar *dol_tail, size_t len)
{
	size_t	i;

	i = 0;
	while (dol_tail)
	{
		if (dol_tail->dkind == WD_DOLLAR)
		{
			// fprintf(stderr, "%s\n", dol_tail->value);
			ft_strlcat(str, dol_tail->value, len + 1);
			while (*dol_tail->value && !ft_isspace(*(dol_tail->value)))
				(dol_tail->value) = (i++, dol_tail->value + 1);
			if (str[len - 1])
				break ;
		}
		else
		{
			ft_memmove(str + i, \
				dol_tail->value, dol_tail->value_len);
			i += dol_tail->value_len;
		}
		dol_tail = dol_tail->next;
	}
}

void	skip_first_space(t_dollar **dol)
{
	size_t	i;

	i = 0;
	while ((*dol) && (*dol)->dkind == WD_DOLLAR)
	{
		while (((*dol)->value)[i] && ft_isspace((*dol)->value[i]))
			i++;
		if (i)
			(*dol)->value += i;
		else if ((*dol)->value[i])
			return ;
		(*dol) = (*dol)->next;
	}
}

size_t	count_word_len(t_dollar **dol)
{
	size_t	len;

	len = 0;
	skip_first_space(dol);
	while ((*dol))
	{
		if (need_split(dol, &len))
			return (len);
		else if ((*dol)->dkind != WD_DOLLAR)
			len += (*dol)->value_len;
		(*dol) = (*dol)->next;
	}
	return (len);
}

static bool	check_first_space(t_dollar **dol, size_t *len)
{
	size_t	i;

	i = 0;
	while (((*dol)->value)[i] && ft_isspace(((*dol)->value)[i]))
		i++;
	if (i)
		(*dol)->value += i;
	if (i && ((*dol)->value)[i])
		return(true);
	else if (i && (*dol)->next && (*dol)->next->dkind != WD_DOLLAR)
		return((*dol) = (*dol)->next, true);
	else if (i && (*dol)->next)
	{
		(*dol) = (*dol)->next;
		return (need_split(dol, len));
	}
	return (false);
}

// need add t_word then true
// else return false
// push_forward dol->value at
// the ptr so that dol_tail can 
// track easily
static bool	need_split(t_dollar **dol, size_t *len)
{
	if ((*dol)->dkind != WD_DOLLAR)
		return (false);
	if (check_first_space(dol, len))
		return (true);
	while (((*dol)->value)[*len] && !ft_isspace(((*dol)->value)[*len]))
		(*len)++;
	if ((*dol)->value[*len])
		return (false);
	return (false);
}