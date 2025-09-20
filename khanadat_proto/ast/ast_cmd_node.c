#include "ast_define.h"
#include "tokenizer_define.h"
#include "status.h"
#include "minishell_err.h"
#include "ast_utils.h"
#include "libft.h"

#ifndef CMD_END
# define CMD_END 3
#endif

static int	set_node_argv(t_token **token, size_t len, t_node *new);
static void	count_argv_len(t_token *token, size_t *len);
static int	add_new_red(t_token *token, t_red **cur);
static int	set_redirection(t_token *token, t_node *new);

t_node	*new_cmd_node(t_token **token)
{
	size_t	len;
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	if (set_redirection(*token, new))
		return ((new->kind = ND_AND), NULL);
	count_argv_len(*token, &len);
	new->argv = ft_calloc(len + 1, sizeof(char *));
	if (!new->argv || set_node_argv(token, len, new))
		return (free_red(new->red), (new->kind = ND_AND), NULL);
	new->kind = ND_CMD;
	return (new);
}

static void	count_argv_len(t_token *token, size_t *len)
{
	*len = 0;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			(*len)++;
			token = token->next;
			continue ;
		}
		if (token->kind == TK_OPERATOR \
			&& (*(token->str) == '>' || *(token->str) == '<'))
		{
			token = token->next->next;
			continue ;
		}
		break ;
	}
}

static int	set_node_argv(t_token **token, size_t len, t_node *new)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if ((*token)->kind != TK_WORD)
		{
			(*token) = ((*token)->next)->next;
			continue ;
		}
		new->argv[i++] = ft_strndup((*token)->str, (*token)->str_len);
		if (!new->argv[i - 1])
		{
			while (i)
				free(new->argv[--i]);
			return (free(new->argv), err_system_call("malloc"), ERR);
		}
		(*token) = (*token)->next;
	}
	while (consume(token, TK_OPERATOR, ND_APPEND) \
	|| consume(token, TK_OPERATOR, ND_HEREDOC) \
	|| consume(token, TK_OPERATOR, ND_RED_IN) \
	|| consume(token, TK_OPERATOR, ND_RED_OUT))
		(*token) = (*token)->next;
	return (SUCCESS);
}

// set redirection's info
static int	set_redirection(t_token *token, t_node *new)
{
	t_red	head;
	t_red	*cur;
	int		status;

	ft_bzero(&head, sizeof(t_red));
	cur = &head;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			token = token->next;
			continue ;
		}
		status = add_new_red(token, &cur);
		token = token->next->next;
		if (status < 0)
			return (status);
		else if (status == CMD_END)
			break ;
	}
	new->red = head.next;
	return (SUCCESS);
}

static int	add_new_red(t_token *token, t_red **cur)
{
	t_red		*new;
	t_NodeKind	nkind;

	if (token->kind != TK_OPERATOR)
		return (CMD_END);
	if (!ft_strncmp(token->str, ">>", 2))
		nkind = ND_APPEND;
	else if (!ft_strncmp(token->str, "<<", 2))
		nkind = ND_HEREDOC;
	else if (*(token->str) == '<')
		nkind = ND_RED_IN;
	else if (*(token->str) == '>')
		nkind = ND_RED_OUT;
	else
		return (CMD_END);
	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (ERR);
	new->kind = nkind;
	new->file = ft_strndup(token->next->str, token->next->str_len);
	if (!new->file)
		return (free(new), ERR);
	(*cur)->next = new;
	(*cur) = new;
	return (SUCCESS);
}
