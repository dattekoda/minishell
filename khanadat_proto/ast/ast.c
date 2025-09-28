/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 11:01:31 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft.h"
#include "status.h"
#include "minishell_err.h"
#include "tokenizer.h"
#include "ast_define.h"
#include "ast_utils.h"

void	free_node(t_node **node)
{
	if (!*node)
		return ;
	free_node(&((*node)->lhs));
	free_node(&((*node)->rhs));
	if ((*node)->kind == ND_CMD)
	{
		free_word((*node)->word);
		free_red((*node)->red);
	}
	free(*node);
	*node = NULL;
}

int	validate_token(t_token *token)
{
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_OPERATOR \
			&& (*(token->str) == '<' \
				|| *(token->str) == '>'))
		{
			if ((token->next)->kind != TK_WORD)
				return (err_tokenizer(token->next), SYNTAX_ERR);
			token = token->next;
		}
		else if (token->kind == TK_OPERATOR
			&& (*(token->str) == '|'
			|| !ft_strncmp(token->str, "&&", 2)))
		{
			if ((token->next)->kind == TK_EOF \
			|| (((token->next)->kind == TK_OPERATOR \
			&& (*((token->next)->str) != '>' \
			&& *((token->next)->str) != '<'))))
				return (err_tokenizer(token->next), SYNTAX_ERR);
			token = token->next;
		}
		token = token->next;
	}
	return (SUCCESS);
}

// syntax err return 2
// system call err return -1
int	get_node(t_node **node, t_token *token)
{
	t_node	*cur;
	t_node	*before;

	if (token->kind == TK_EOF || validate_token(token))
		return (SYNTAX_ERR);
	cur = new_pipe_node(&token);
	while (cur)
	{
		before = cur;
		if (consume_node(&token, TK_OPERATOR, ND_OR))
			cur = new_node(ND_OR, cur, new_pipe_node(&token));
		else if (consume_node(&token, TK_OPERATOR, ND_AND))
			cur = new_node(ND_AND, cur, new_pipe_node(&token));
		else
			break ;
	}
	if (!cur)
		return (free_node(&before), ERR);
	*node = cur;
	return (SUCCESS);
}
