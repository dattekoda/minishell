/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 16:23:53 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"
#include "expand.h"
#include "expand_define.h"
#include "expand_utils.h"
#include "libft.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"

static void	set_new_word(t_word **new, t_word *before, t_mini *mini);
static int	set_new_red(t_red **new, t_red *before, t_mini *mini);

// if ambiguous redirect, return FAILURE;
int	expand_node(t_node *node, t_mini *mini)
{
	t_word	*before_word;
	t_word	*new_word;
	t_red	*before_red;
	t_red	*new_red;

	if (node->word)
	{
		before_word = node->word;
		set_new_word(&new_word, before_word, mini);
		free_word(node->word);
		node->word = new_word;
	}
	if (!node->red)
		return (SUCCESS);
	before_red = node->red;
	if (set_new_red(&new_red, before_red, mini))
		return (FAILURE);
	free_red(before_red);
	node->red = new_red;
	return (SUCCESS);
}

// void	dol_checker(t_dollar *dol)
// {
// 	while (dol)
// 	{
// 		if (dol->dkind == WD_WORD)
// 		{
// 			fprintf(stderr, "val:	%s\n", dol->value);
// 			fprintf(stderr, "len:	%zu\n", dol->value_len);
// 		}
// 		else if (dol->dkind == WD_SPACE)
// 			fprintf(stderr, "space\n");
// 		fprintf(stderr, "\n");
// 		dol = dol->next;
// 	}
// }

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

	ft_bzero(&head, sizeof(t_word));
	cur = &head;
	while (before && cur)
	{
		if (get_dollar(before->file, mini, &dol))
			systemcall_minishell_exit((free_red(head.next), \
			mini), "malloc");
		dol_head = dol;
		cur = add_new_red(cur, &dol, before->kind);
		if (dol || !*cur->file)
			return (free_dollar(dol_head), free(head.next), \
			err_ambiguous(before->file), ERR);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!cur)
		systemcall_minishell_exit((free_red(head.next), \
		mini), "malloc");
	*new = head.next;
	return (SUCCESS);
}
