/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_new_node_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 18:05:05 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_bonus.h"
#include "ast_define_bonus.h"
#include "ast_utils_bonus.h"
#include "tokenizer_define_bonus.h"

t_node	*new_pipe_node(t_token **token)
{
	t_node	*node;
	t_node	*before;

	node = new_cmd_node(token);
	while (consume_node(token, TK_OPERATOR, ND_PIPE) && node)
	{
		before = node;
		node = new_node(ND_PIPE, node, new_cmd_node(token));
	}
	if (!node)
		return (free_node(&before), NULL);
	return (node);
}

t_node	*new_and_or_node(t_token **token)
{
	t_node	*cur;
	t_node	*before;

	before = NULL;
	cur = new_pipe_node(token);
	while (cur)
	{
		before = cur;
		if (consume_node(token, TK_OPERATOR, ND_OR))
			cur = new_node(ND_OR, cur, new_pipe_node(token));
		else if (consume_node(token, TK_OPERATOR, ND_AND))
			cur = new_node(ND_AND, cur, new_pipe_node(token));
		else
			break ;
	}
	if (!cur)
		return (free_node(&before), NULL);
	return (cur);
}

t_node	*new_inside_node(t_token **token)
{
	t_node	*cur;

	if (consume_node(token, TK_OPERATOR, ND_PAR_FIRST))
	{
		cur = new_node(ND_INSIDE, new_and_or_node(token), NULL);
		consume_node(token, TK_OPERATOR, ND_PAR_SEC);
		return (cur);
	}
	return (new_and_or_node(token));
}
