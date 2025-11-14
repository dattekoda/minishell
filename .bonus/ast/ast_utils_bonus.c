/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:42 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_define_bonus.h"
#include "ast_utils_bonus.h"
#include "tokenizer_bonus.h"
#include "minishell_err_bonus.h"
#include "libft.h"
#include "ast_bonus.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

t_node	*new_node(t_NodeKind kind, t_node *lhs, t_node *rhs)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->kind = kind;
	new->lhs = lhs;
	new->rhs = rhs;
	return (new);
}

bool	consume_redirect(t_token **token, t_TokenKind tkind, t_RedKind rkind)
{
	if ((*token)->kind != tkind)
		return (false);
	if ((*token)->kind == TK_OPERATOR)
	{
		if (rkind == RD_HEREDOC && ft_strncmp((*token)->str, "<<", 2))
			return (false);
		if (rkind == RD_APPEND && ft_strncmp((*token)->str, ">>", 2))
			return (false);
		if (rkind == RD_IN \
			&& !(*((*token)->str) == '<' && *((*token)->str + 1) != '<'))
			return (false);
		if (rkind == RD_OUT \
			&& !(*((*token)->str) == '>' && *((*token)->str + 1) != '>'))
			return (false);
	}
	(*token) = (*token)->next;
	return (true);
}

bool	consume_node(t_token **token, t_TokenKind tkind, t_NodeKind nkind)
{
	if ((*token)->kind != tkind)
		return (false);
	if ((*token)->kind == TK_OPERATOR)
	{
		if (nkind == ND_AND && ft_strncmp((*token)->str, "&&", 2))
			return (false);
		if (nkind == ND_OR && ft_strncmp((*token)->str, "||", 2))
			return (false);
		if (nkind == ND_PIPE \
			&& !(*((*token)->str) == '|' && *((*token)->str + 1) != '|'))
			return (false);
		if (nkind == ND_PAR_FIRST && !(*((*token)->str) == '('))
			return (false);
		if (nkind == ND_PAR_SEC && !(*((*token)->str) == ')'))
			return (false);
	}
	(*token) = (*token)->next;
	return (true);
}
