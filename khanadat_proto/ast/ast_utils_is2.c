/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_is2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:02:55 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 12:05:35 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_define.h"
#include "ast_utils.h"
#include <stdbool.h>

bool	is_par_first(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == '(');
}

bool	is_par_sec(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	return (*(token->str) == ')');
}
