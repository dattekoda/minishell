#include "tokenizer.h"
#include "status.h"
#include "libft.h"
#include <stdlib.h>

static t_token	*new_word_token(t_token *token, \
	char **str, t_token *cur);
static t_token	*new_token(TokenKind kind, char **str, t_token *cur);
static t_token	*special_token(char **str, t_token *cur);

int	get_token(t_token **token, char *line)
{
	t_token	*cur;

	cur = *token;
	while (cur && *line) {
		if (ft_isspace(*line))
		{
			line++;
			continue ;
		}
		if (!ft_strchr(SPECIALS, *line))
		{
			cur = new_token(TK_WORD, &line, cur);
			continue ;
		}
		cur = special_token(&line, cur);
	}
	if (!cur)
		return (free_token((*token)->next), ERR);
	return (SUCCESS);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->kind == TK_WORD)
			free(token->str);
		free(token);
		token = tmp;
	}
}

static t_token	*new_word_token(t_token *token, \
	char **str, t_token *cur)
{
	char	*tmp;
	char	*chr;

	tmp = *str;
	while (**str && !ft_isspace(**str) && !ft_strchr(SPECIALS, **str))
	{
		if (**str == '\'' || **str == '\"')
		{
			chr = ft_strchr(*str + 1, **str);
			*str = chr + 1;
			continue ;
		}
		while (**str && !ft_isspace(**str) && \
		!ft_strchr(SPECIALS, **str) && **str != '\'' && **str != '\"')
			(*str)++;
	}
	token->str = ft_strndup(tmp, (*str) - tmp);
	if (!token->str)
		return (free(token), (cur->next = NULL), NULL);
	return (token);
}

static t_token	*new_token(TokenKind kind, char **str, t_token *cur)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->kind = kind;
	token->str = NULL;
	cur->next = token;
	if (kind == TK_PIPE || kind == TK_REDIR_IN || kind == TK_REDIR_OUT)
		return ((*str)++, token);
	if (kind == TK_HERE_DOC || kind == TK_APPEND \
		|| kind == TK_OR || kind == TK_AND)
		return (((*str) += 2), token);
	return (new_word_token(token, str, cur));
}

static t_token	*special_token(char **str, t_token *cur)
{
	if (**str == '|' && *(*str + 1) != '|')
		return (new_token(TK_PIPE, str, cur));
	if (**str == '<' && *(*str + 1) != '<')
		return (new_token(TK_REDIR_IN, str, cur));
	if (**str == '>' && *(*str + 1) != '>')
		return (new_token(TK_REDIR_OUT, str, cur));
	if (!ft_strncmp(*str, "<<", 2))
		return (new_token(TK_HERE_DOC, str, cur));
	if (!ft_strncmp(*str, ">>", 2))
		return (new_token(TK_APPEND, str, cur));
	if (!ft_strncmp(*str, "&&", 2))
		return (new_token(TK_AND, str, cur));
	if (!ft_strncmp(*str, "||", 2))
		return (new_token(TK_OR, str, cur));
	return (NULL);
}
