/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:35:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:35:54 by khanadat         ###   ########.fr       */
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

// if system call err, exit
int	expand_word(t_node *node, t_mini *mini)
{
	t_word	*before;
	t_word	*new;

	before = node->word;
	if (set_new_word(&new, before, mini))
		return (ERR);
	free_word(node->word);
	node->word = new;
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
		if (search_dollar(before, mini, &dol))
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
