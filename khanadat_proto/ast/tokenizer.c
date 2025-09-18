#include <stdlib.h>
#include "status.h"
#include "minishell_err.h"
#include "tokenizer.h"
#include "libft.h"

static t_token	*new_reserved_token(t_token *cur, char **str);
static t_token	*new_word_token(t_token *cur, char **str);
static t_token	*new_eof_token(t_token *cur);

int	get_token(t_token *cur, char *line)
{
	while (*line && cur)
	{
		if (ft_isspace(*line))
		{
			line++;
			continue ;
		}
		if (*line == '|' || *line == '&')
		{
			cur = new_reserved_token(cur, &line);
			continue ;
		}
		cur = new_word_token(cur, &line);
	}
	if (!cur)
		return (ERR);
	if (!new_eof_token(cur))
		return (ERR);
	return (SUCCESS);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

static t_token	*new_reserved_token(t_token *cur, char **str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (err_system_call("malloc"), NULL);
	cur->next = new;
	if (!ft_strncmp(*str, "||", 2))
	{
		(*str) += 2;
		new->kind = TK_OR;
	}
	else if (!ft_strncmp(*str, "&&", 2))
	{
		(*str) += 2;
		new->kind = TK_AND;
	}
	else if (**str == '|')
		new->kind = ((*str)++, TK_PIPE);
	else if (**str == '&')
	{
		put_err('&');
		new->str = (*str)++;
		new->kind = TK_WORD;
	}
	return (new);
}

static t_token	*new_word_token(t_token *cur, char **str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (err_system_call("malloc"), NULL);
	new->kind = TK_WORD;
	cur->next = new;
	new->str = *str;
	while (**str && !ft_isspace(**str) \
			&& **str != '&' && **str != '|')
		(*str)++;
	new->str_len = (size_t)((*str) - new->str);
	return (new);
}

static t_token	*new_eof_token(t_token *cur)
{
	t_token	*new;

	new = calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->kind = TK_EOF;
	cur->next = new;
	return (new);
}
