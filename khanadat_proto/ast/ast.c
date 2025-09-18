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
	}
	free(node);
	node = NULL;
}

int	get_node(t_node **node, t_token *token)
{
	t_node	*cur;

	cur = pipe_node(&token);
	*node = cur;
	while (cur)
	{
		if (consume(&token, TK_OR))
			cur = new_node(ND_OR, cur, pipe_node(&token));
		else if (consume(&token, TK_AND))
			cur = new_node(ND_AND, cur, pipe_node(&token));
		else
			break ;
	}
	if (!cur)
		return (free_node(*node), ERR);
	*node = cur;
	return (SUCCESS);
}
