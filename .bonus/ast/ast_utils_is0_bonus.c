/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_is0_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:02:03 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "tokenizer_define_bonus.h"
#include "ast_utils_bonus.h"

bool	is_pipe_or_and(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (is_pipe(token) \
	|| is_or(token) \
	|| is_and(token));
}

bool	is_or_and(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (is_or(token) || is_and(token));
}

bool	is_pipe(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '|' \
	&& *(token->str + 1) != '|');
}

bool	is_and(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '&' \
	&& *(token->str + 1) == '&');
}

bool	is_or(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '|' \
	&& *(token->str + 1) == '|');
}
