/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:25:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/13 19:05:34 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_define.h"
#include "minishell_define.h"
#include "add_new_utils.h"
#include "libft.h"

t_word	*add_new_word(t_word *cur, t_dollar **dol)
{
	t_word		*new_word;
	t_dollar	*dol_tail;

	new_word = ft_calloc(1, sizeof(t_word));
	if (!new_word)
		return (NULL);
	cur->next = new_word;
	dol_tail = *dol;
	new_word->exp_len = count_word_len(dol);
	new_word->expanded = ft_calloc(new_word->exp_len + 1, sizeof(char));
	if (!new_word->expanded)
		return (NULL);
	set_new_str(new_word->expanded, dol_tail);
	return (new_word);
}

t_red	*add_new_red(t_red *cur, t_dollar **dol, t_RedKind rk)
{
	t_red		*new_red;
	t_dollar	*dol_tail;

	new_red = ft_calloc(1, sizeof(t_red));
	if (!new_red)
		return (NULL);
	cur->next = new_red;
	new_red->kind = rk;
	dol_tail = *dol;
	new_red->exp_len = count_word_len(dol);
	new_red->expanded = ft_calloc(new_red->exp_len + 1, sizeof(char));
	if (!new_red->expanded)
		return (NULL);
	set_new_str(new_red->expanded, dol_tail);
	return (new_red);
}
