#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ast_define.h"
#include "tokenizer.h"
#include "status.h"
#include "minishell_err.h"
#include "libft.h"
#include "ast.h"

t_node	*new_cmd_node(t_token **token);

void	free_red(t_red *head)
{
	t_red	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->file);
		free(head);
		head = tmp;
	}
}

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

bool	consume(t_token **token, t_TokenKind tkind, t_NodeKind nkind)
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
		if (nkind == ND_RED_IN \
			&& !(*((*token)->str) == '<' && *((*token)->str + 1) != '<'))
		if (nkind == ND_RED_OUT \
			&& !(*((*token)->str) == '>' && *((*token)->str + 1) != '>'))
			return (false);
		if (nkind == ND_HEREDOC && ft_strncmp((*token)->str, "<<", 2))
			return (false);
		if (nkind == ND_APPEND && ft_strncmp((*token)->str, ">>", 2))
			return (false);
	}
	(*token) = (*token)->next;
	return (true);
}

t_node	*pipe_node(t_token **token)
{
	t_node	*node;
	t_node	*before;

	node = new_cmd_node(token);
	while (consume(token, TK_OPERATOR, ND_PIPE) && node)
	{
		before = node;
		node = new_node(ND_PIPE, node, new_cmd_node(token));
	}
	if (!node)
		return (free_node(before), NULL);
	return (node);
}
