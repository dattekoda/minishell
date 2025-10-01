/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand_utils_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:25:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/02 00:11:32 by khanadat         ###   ########.fr       */
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
	new_word->word_len = count_word_len(dol);
	new_word->word = ft_calloc(new_word->word_len + 1, sizeof(char));
	if (!new_word->word)
		return (free(new_word), NULL);
	set_new_str(new_word->word, dol_tail);
	return (new_word);
}

t_red	*add_new_red(t_red *cur, t_dollar **dol, t_RedKind rk)
{
	t_red		*new_red;
	t_dollar	*dol_tail;
	size_t		file_len;

	new_red = ft_calloc(1, sizeof(t_word));
	if (!new_red)
		return (NULL);
	cur->next = new_red;
	new_red->kind = rk;
	dol_tail = *dol;
	file_len = count_word_len(dol);
	new_red->file = ft_calloc(file_len + 1, sizeof(char));
	if (!new_red->file)
		return (free(new_red), NULL);
	set_new_str(new_red->file, dol_tail);
	return (new_red);
}
