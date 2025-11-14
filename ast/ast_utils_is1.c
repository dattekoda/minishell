/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_is1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:02:31 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 12:05:30 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_define.h"
#include "ast_utils.h"
#include <stdbool.h>

bool	is_redirect(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (is_red_in(token) \
	|| is_red_out(token) \
	|| is_red_append(token) \
	|| is_red_heredoc(token));
}

bool	is_red_in(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '>' \
	&& *(token->str + 1) != '>');
}

bool	is_red_out(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '<' \
	&& *(token->str + 1) != '<');
}

bool	is_red_append(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '>' \
	&& *(token->str + 1) == '>');
}

bool	is_red_heredoc(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '<' \
	&& *(token->str + 1) == '<');
}
