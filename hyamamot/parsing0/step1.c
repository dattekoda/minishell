#include <stdio.h>
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

// ヘルパー関数
static int	is_ident_start(int c)
{
	return (isalpha(c) || c == '_');
}

static int	is_ident_rest(int c)
{
	return (isalnum(c) || c == '_');
}

// 元の文字列のアドレスを使っている
static Token	next_token(const char **p)
{
	Token			t;
	unsigned char	c;

	while (isspace(**p))
		(*p)++;
	t.kind = T_ERR;
	t.start = *p;
	t.end = *p;
	c = (unsigned char)**p;
	if (c == '\0' || c == '\n')
	{
		t.kind = T_END;
		return (t);
	}
	if (c == '=')
	{
		(*p)++;
		t.end = *p;
		t.kind = T_EQ;
		return (t);
	}
	if (c == ';')
	{
		(*p)++;
		t.end = *p;
		t.kind = T_SEMI;
		return (t);
	}
	if (is_ident_start(c))
	{
		(*p)++;
		while (is_ident_rest(**p))
			(*p)++;
		t.end = *p;
		t.kind = T_IDENT;
		return (t);
	}
	// 不明文字
	(*p)++;
	t.end = *p;
	t.kind = T_ERR;
	return (t);
}

int	main(void)
{
	char		line[4096];
	const char	*p;
	Token		tk;
	int			len;

	printf("pairs> ");
	while (fgets(line, sizeof line, stdin))
	{
		p = line;
		while (1)
		{
			tk = next_token(&p);
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