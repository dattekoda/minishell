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

void	put_token_err(t_token *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token->kind == TK_EOF)
		ft_putstr_fd("new_line", STDERR_FILENO);
	else if (token->kind == TK_OPERATOR)
		write(STDERR_FILENO, token->str, token->str_len);
	ft_putstr_fd("\'", STDERR_FILENO);
}

void	free_node(t_node *node)
{
	size_t	i;

	if (!node)
		return ;
	free_node(node->lhs);
	free_node(node->rhs);
	if (node->kind == ND_CMD)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
		free_red(node->red);
	}
	free(node);
	node = NULL;
}

int	validate_token(t_token *token)
{
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_OPERATOR \
			&& (*(token->str) == '<' \
				|| *(token->str) == '>' \
				|| !ft_strncmp(token->str, "||", 2) \
				|| !ft_strncmp(token->str, "&&", 2)))
		{
			if ((token->next)->kind != TK_WORD)
				return (put_token_err(token->next), SYNTAX_ERR);
			token = token->next;
		}
		else if (token->kind == TK_OPERATOR
			&& *(token->str) == '|')
		{
			if (!((token->next)->kind == TK_WORD \
			|| *((token->next)->str) == '>'))
				return (put_token_err(token->next), SYNTAX_ERR);
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
		if (consume(&token, TK_OPERATOR, ND_OR))
			cur = new_node(ND_OR, cur, new_pipe_node(&token));
		else if (consume(&token, TK_OPERATOR, ND_AND))
			cur = new_node(ND_AND, cur, new_pipe_node(&token));
		else
			break ;
	}
	if (!cur)
		return (free_node(before), ERR);
	*node = cur;
	return (SUCCESS);
}
