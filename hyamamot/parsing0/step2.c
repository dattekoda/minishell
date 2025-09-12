// Lexerを導入して状態をまとめる

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum
{
	T_IDENT,
	T_EQ,
	T_SEMI,
	T_END,
	T_ERR,
}	TokenKind;

typedef struct
{
	TokenKind	kind;
	const char	*start;
	const char	*end;
}	Token;

typedef struct
{
	const char	*p;
}	Lexer;

// ヘルパー関数
static int	is_ident_start(int c)
{
	return (isalpha(c) || c == '_');
}

static int	is_ident_rest(int c)
{
	return (isalnum(c) || c == '_');
}

static void	skip_spaces(Lexer *L)
{
	while (isspace(*(L->p)))
	{
		L->p++;
	}
}

static Token	next_token(Lexer *L)
{
	Token			t;
	unsigned char	c;

	skip_spaces(L);
	t.kind = T_ERR;
	t.start = L->p;
	t.end = L->p;
	c = (unsigned char)(*(L->p));
	if (c == '\0' || c == '\n')
	{
		t.kind = T_END;
		return (t);
	}
	if (c == '=')
	{
		L->p++;
		t.end = L->p;
		t.kind = T_EQ;
		return (t);
	}
	if (c == ';')
	{
		L->p++;
		t.end = L->p;
		t.kind = T_SEMI;
		return (t);
	}
	if (is_ident_start(*L->p))
	{
		L->p++;
		while (is_ident_rest(*L->p))
			L->p++;
		t.end = L->p;
		t.kind = T_IDENT;
		return (t);
	}
	L->p++;
	t.end = L->p;
	t.kind = T_ERR;
	return (t);
}

int	main(void)
{
	char	line[4096];
	Lexer	L;
	Token	tk;
	int		len;

	printf("pairs> ");
	while (fgets(line, sizeof line, stdin))
	{
		L.p = line;
		while (1)
		{
			tk = next_token(&L);
			len = (int)(tk.end - tk.start);
			if (tk.kind == T_IDENT)
				printf("IDENT(\"%.*s\")\n", len, tk.start);
			else if (tk.kind == T_EQ)
				printf("EQ(=)\n");
			else if (tk.kind == T_SEMI)
				printf("SEMI(;)\n");
			else if (tk.kind == T_END)
				printf("END\n");
			else
				printf("ERR(\"%.*s\")\n", len, tk.start);
			if (tk.kind == T_END)
				break ;
		}
		printf("pairs> ");
	}
	return (0);
}