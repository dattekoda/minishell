#ifndef TOKENIZER_DEFINE_H
# define TOKENIZER_DEFINE_H

# include <stddef.h>

typedef enum s_TokenKind
{
	TK_WORD,
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_EOF,
}	t_TokenKind;

typedef struct s_token
{
	char			*str;
	size_t			str_len;
	t_TokenKind		kind;
	struct s_token	*next;
}	t_token;

#endif