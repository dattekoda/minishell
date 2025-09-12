#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_token		t_token;
enum e_token_kind {
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
};
typedef enum e_token_kind	t_token_kind;

// `word` is zero terminated string.
struct s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

bool	startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}

/*
metacharacter
	  A character that, when unquoted, separates words.  One of the following:
	  |  & ; ( ) < > space tab
control operator
	  A token that performs a control function.  It is one of the following symbols:
	  || & && ; ;; ( ) | <newline>
*/
bool	is_operator(const char *s)
{
	static char	*const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;				

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
       word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
       name   A word consisting only of alphanumeric characters and underscores, and beginning with an alphabetic
              character or an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.  One of the following:
              |  & ; ( ) < > space tab
       control operator
              A token that performs a control function.  It is one of the following symbols:
              || & && ; ;; ( ) | <newline>
*/
bool	is_metacharacter(char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

t_token	*operator(char **rest, char *line)
{
	static char	*const	operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i = 0;				
	char				*op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
		line++;
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}

t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*tok;

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line))
			tok = tok->next = operator(&line, line);
		else if (is_word(line))
			tok = tok->next = word(&line, line);
		else
			assert_error("Unexpected Token");
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}