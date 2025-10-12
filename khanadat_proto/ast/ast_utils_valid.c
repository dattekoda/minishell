/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:50:11 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/12 19:18:20 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define.h"
#include "minishell_err.h"
#include "tokenizer_define.h"
#include "ast_utils.h"

static int	validate_inside(t_token **token);
static int	token_checker(t_token **token);

int	validate_token(t_token *token)
{
	if (is_pipe_or_and(token))
		return (err_tokenizer(token), SYNTAX_ERR);
	while (token->kind != TK_EOF)
	{
		if (token_checker(&token))
			return (SYNTAX_ERR);
		token = token->next;
	}
	return (SUCCESS);
}

static int	validate_inside(t_token **token)
{
	*token = (*token)->next;
	if (is_pipe_or_and(*token) || is_par_sec(*token))
		return (err_tokenizer(*token), SYNTAX_ERR);
	while ((*token)->kind != TK_EOF && !is_par_sec(*token))
	{
		if ((token_checker(token)))
			return (SYNTAX_ERR);
		*token = (*token)->next;
	}
	if ((*token)->kind == TK_EOF)
		return (err_tokenizer((*token)->next), SYNTAX_ERR);
	return (SUCCESS);
}

static int	token_checker(t_token **token)
{
	if (is_redirect((*token)))
	{
		if (((*token)->next)->kind != TK_WORD)
			return (err_tokenizer((*token)->next), SYNTAX_ERR);
	}
	else if (is_pipe_or_and((*token)))
	{
		if (((*token)->next)->kind == TK_EOF \
		|| is_pipe_or_and((*token)->next) || is_par_sec((*token)->next))
			return (err_tokenizer((*token)->next), SYNTAX_ERR);
	}
	else if (is_par_first((*token)))
	{
		if (validate_inside(token))
			return (SYNTAX_ERR);
		if (is_par_first((*token)->next) || (*token)->next->kind == TK_WORD)
			return (err_tokenizer((*token)->next), SYNTAX_ERR);
	}
	else if ((*token)->kind == TK_WORD)
	{
		if (is_par_first((*token)->next))
			return (err_tokenizer((*token)->next->next), SYNTAX_ERR);
	}
	return (SUCCESS);
}
