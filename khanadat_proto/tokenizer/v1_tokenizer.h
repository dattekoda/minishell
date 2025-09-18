#ifndef V1_TOKENIZER_H
# define V1_TOKENIZER_H

# define SPECIALS "|<>&"

typedef enum {
	TK_WORD,
	TK_PIPE, // |
	TK_OR, // ||
	TK_AND, // &&
	TK_REDIR_IN, // <
	TK_REDIR_OUT, // >
	TK_HERE_DOC, // <<
	TK_APPEND, // >>
}	TokenKind;

typedef struct s_token{
	TokenKind		kind;
	char			*str;
	struct s_token	*next;
}	t_token;

// validate.c
int			validate(char *line);

// token.c
int			get_token(t_token **token, char *line);
void		free_token(t_token *token);

#endif