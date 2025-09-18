#include <stdbool.h>
#include <stdlib.h>
#include "ast_define.h"
#include "tokenizer.h"
#include "status.h"
#include "minishell_err.h"
#include "libft.h"

t_node	*new_node(NodeKind kind, t_node *lhs, t_node *rhs)
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

static int	set_node_argv(t_token **head, t_token *tail, t_node *new)
{
	size_t	i;
	i = 0;
	
	while ((*head) != tail)
	{
		new->argv[i++] = ft_strndup((*head)->str, (*head)->str_len);
		if (!new->argv[i - 1])
		{
			while (i)
				free(new->argv[(--i)]);
			return (free(new->argv), err_system_call("malloc"), ERR);
		}
		(*head) = (*head)->next;
	}
	return (SUCCESS);
}

static t_node	*new_cmd_node(t_token **head)
{
	t_node	*new;
	t_token	*tail;
	size_t	len;

	len = 0;
	tail = (*head);
	while (tail && tail->kind == TK_WORD)
		tail = (len++, tail->next);
	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->argv = ft_calloc(len + 1, sizeof(char *));
	if (!new->argv || set_node_argv(head, tail, new))
		return ((new->kind = ND_AND), NULL);
	new->kind = ND_CMD;
	return (new);
}

bool	consume(t_token **token, t_TokenKind kind)
{
	if ((*token)->kind != kind)
		return (false);
	(*token) = (*token)->next;
	return (true);
}

t_node	*pipe_node(t_token **token)
{
	t_node	*node;

	node = new_cmd_node(token);
	while (consume(token, TK_PIPE) && node)
		node = new_node(ND_PIPE, node, new_cmd_node(token));
	return (node);
}
