/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_bonus.h"
#include "expand_bonus.h"
#include "expand_define_bonus.h"
#include "expand_utils_bonus.h"
#include "libft.h"
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"

static void	set_new_word(t_word **new, t_word *before, t_mini *mini);
static int	set_new_red(t_red **new, t_red *before, t_mini *mini);

// if ambiguous redirect, return FAILURE;
int	expand_node(t_node *node, t_mini *mini)
{
	t_word	*new_word;
	t_red	*new_red;

	if (node->word)
	{
		set_new_word(&new_word, node->word, mini);
		free_word(node->word);
		node->word = new_word;
		set_wild_word(mini, &node->word);
	}
	if (!node->red)
		return (SUCCESS);
	if (set_new_red(&new_red, node->red, mini))
		return (FAILURE);
	free_red(node->red);
	node->red = new_red;
	if (set_wild_red(mini, &node->red))
		return (FAILURE);
	return (SUCCESS);
}

static void	set_new_word(t_word **new, t_word *before, t_mini *mini)
{
	t_word		head;
	t_word		*cur;
	t_dollar	*dol;
	t_dollar	*dol_head;

	ft_bzero(&head, sizeof(t_word));
	cur = &head;
	while (before && cur)
	{
		if (get_dollar(before->word, mini, &dol))
			systemcall_minishell_exit((free_word(head.next), \
			mini), "malloc");
		dol_head = dol;
		while (dol && cur)
			cur = add_new_word(cur, &dol);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!cur)
		systemcall_minishell_exit((free_word(head.next), \
		mini), "malloc");
	*new = head.next;
}

static int	set_new_red(t_red **new, t_red *before, t_mini *mini)
{
	t_red		head;
	t_red		*cur;
	t_dollar	*dol;
	t_dollar	*dol_head;

	ft_bzero(&head, sizeof(t_red));
	cur = &head;
	while (before && cur)
	{
		if (get_dollar(before->file, mini, &dol))
			systemcall_minishell_exit((free_red(head.next), \
			mini), "malloc");
		dol_head = dol;
		cur = add_new_red(cur, &dol, before);
		if (dol || !*cur->expanded)
			return (free_dollar(dol_head), free(head.next), \
			err_ambiguous(before->file), FAILURE);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!cur)
		systemcall_minishell_exit((free_red(head.next), \
		mini), "malloc");
	*new = head.next;
	return (SUCCESS);
}
