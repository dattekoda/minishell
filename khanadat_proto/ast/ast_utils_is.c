/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_is.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:53:20 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/06 15:53:28 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "tokenizer_define.h"
#include "libft.h"

bool	is_pipe_or_and(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	if (*(token->str) == '|' \
	|| !ft_strncmp(token->str, "&&", 2))
		return (true);
	return (false);
}

bool	is_redirect(t_token *token)
{
	if (token->kind != TK_OPERATOR)
		return (false);
	if (*(token->str) == '>' || *(token->str) == '<')
		return (true);
	return (false);
}
