/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/01 14:02:53 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ast.h"
#include "expand.h"
#include "status.h"
#include "libft.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "expand_define.h"
#include "expand_utils.h"

static int	set_new_word(t_word **new, t_word *before, t_mini *mini);
static int	set_new_red(t_red **new, t_red *before, t_mini *mini);

// if system call err, exit
int	expand_node(t_node *node, t_mini *mini)
{
	t_word	*before_word;
	t_word	*new_word;
	t_red	*before_red;
	t_red	*new_red;

	before_word = node->word;
	if (set_new_word(&new_word, before_word, mini))
		return (ERR);
	free_word(node->word);
	node->word = new_word;
	if (!node->red)
		return (SUCCESS);
	before_red = node->red;
	if (set_new_red(&new_red, before_red, mini))
		return (ERR);
	free_red(before_red);
	node->red = new_red;
	return (SUCCESS);
}

static int	set_new_word(t_word **new, t_word *before, t_mini *mini)
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
			return (free_word(head.next), ERR);
		dol_head = dol;
		while (dol && cur)
			cur = add_new_word(cur, &dol);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!new)
		return (free_word(head.next), ERR);
	*new = head.next;
	return (SUCCESS);
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
			return (free_red(head.next), ERR);
		dol_head = dol;
		cur = add_new_red(cur, &dol, before->kind);
		if (dol)
			failure_minishell_exit((free_dollar(dol_head), \
			free(head.next), mini), err_ambiguous, before->file);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!new)
		return (free_red(head.next), ERR);
	*new = head.next;
	return (SUCCESS);
}
