/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:25:08 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 18:00:30 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_define.h"
#include "minishell_define.h"
#include "add_new_utils.h"
#include "libft.h"

static bool	check_is_quoted(t_dollar *dol);
static void	set_orig_file(t_red *red, const t_dollar *dol);

t_word	*add_new_word(t_word *cur, t_dollar **dol)
{
	t_word		*new_word;
	t_dollar	*dol_tail;

	new_word = ft_calloc(1, sizeof(t_word));
	if (!new_word)
		return (NULL);
	dol_tail = *dol;
	cur->next = new_word;
	new_word->exp_len = count_word_len(dol);
	new_word->expanded = ft_calloc(new_word->exp_len + 1, sizeof(char));
	if (!new_word->expanded)
		return (NULL);
	new_word->wild_checker = ft_calloc(new_word->exp_len, sizeof(bool));
	if (!new_word->wild_checker)
		return (NULL);
	set_new_str(new_word->expanded, dol_tail);
	set_wild_checker(new_word->wild_checker, dol_tail);
	return (new_word);
}

t_red	*add_new_red(t_red *cur, t_dollar **dol, t_red *before)
{
	t_red		*new_red;
	t_dollar	*dol_tail;

	new_red = ft_calloc(1, sizeof(t_red));
	if (!new_red)
		return (NULL);
	dol_tail = *dol;
	cur->next = new_red;
	new_red->kind = before->kind;
	new_red->exp_len = count_word_len(dol);
	new_red->expanded = ft_calloc(new_red->exp_len + 1, sizeof(char));
	if (!new_red->expanded)
		return (NULL);
	new_red->wild_checker = ft_calloc(new_red->exp_len, sizeof(bool));
	if (!new_red->wild_checker)
		return (NULL);
	if (check_is_quoted(dol_tail))
		new_red->is_quoted = true;
	new_red->file = before->file;
	set_new_str(new_red->expanded, dol_tail);
	set_orig_file(new_red, dol_tail);
	set_wild_checker(new_red->wild_checker, dol_tail);
	return (new_red);
}

static bool	check_is_quoted(t_dollar *dol)
{
	while (dol)
	{
		if (dol->is_quoted)
			return (true);
		dol = dol->next;
	}
	return (false);
}

// dol->orig is original str like $HOME
static void	set_orig_file(t_red *red, const t_dollar *dol)
{
	size_t			i;
	const t_dollar	*tmp;

	tmp = dol;
	while (tmp && tmp->dkind != WD_SPACE)
	{
		if (tmp->orig)
		{
			i = 1;
			while (tmp->orig[i] && !ft_strchr(DOL_DELIMITER, tmp->orig[i]) \
				&& !ft_isspace(tmp->orig[i]))
				i++;
			ft_memmove(red->file + red->file_len, tmp->orig, i);
			red->file_len += i;
		}
		else
		{
			ft_memmove(red->file + red->file_len, tmp->value, tmp->value_len);
			red->file_len += tmp->value_len;
		}
		tmp = tmp->next;
	}
	red->file[red->file_len] = '\0';
}
