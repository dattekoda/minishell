// 先読みを導入 && Tokenでstart,endの代わりにmallocで文字列を保持

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
	T_IDENT,
	T_EQ,
	T_SEMI,
	T_END,
	T_ERR
}	TokenKind;


typedef struct
{
	TokenKind	kind;
	char		*text;
	const char	*lexeme_start; // エラー表示用 (この位置からおかしいよ)
}	Token;

typedef struct
{
	const char	*p;
	int			has_peek;
	Token		peeked;
}	Lexer;

// ヘルパー関数
static void	*xmalloc(size_t n)
{
	void	*p;

	p = malloc(n);
	if (!p)
	{
		fprintf(stderr, "oom\n");
		exit(1);
	}
	return (p);
}

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
	while (*L->p == ' ' || *L->p == '\t')
		L->p++;
}

// identまでを読み取ってmallocしてその文字列を返す
// stdinから読み取った文字列をendpに設定して、読んだ分は進める
static char *read_ident(const char *s, const char **endp)
{
	const char	*p;
	size_t		n;
	char		*text;

	p = s;
	if (!is_ident_start((unsigned char)*p))
		return (NULL);
	p++;
	while (is_ident_rest((unsigned char)*p))
		p++;
	n = (size_t)(p - s);
	text = xmalloc(n + 1);
	memcpy(text, s, n);
	text[n] = '\0';
	*endp = p;
	return (text);
}

static Token	next_raw(Lexer *L)
{
	Token			t;
	unsigned char	c;

	skip_spaces(L);
	// 初期化
	t.kind = T_ERR;
	t.lexeme_start = L->p;
	t.text = NULL;
	c = (unsigned char)*L->p;
	if (c == '\0' || c == '\n')
	{
		t.kind = T_END;
		return (t);
	}
	if (c == '=')
	{
		t.kind = T_EQ;
		L->p++;
		return (t);
	}
	if (c == ';')
	{
		t.kind = T_SEMI;
		L->p++;
		return (t);
	}
	if (is_ident_start(c))
	{
		t.kind = T_IDENT;
		t.text = read_ident(L->p, &L->p);
		return (t);
	}
	// どこにも引っかからない時はT_ERRのまま返す
	return (t);
}

static void	lexer_init(Lexer *L, const char *in)
{
	L->p = in;
	L->has_peek = 0;
}

static Token	lexer_peek(Lexer *L)
{
	if (!L->has_peek)
	{
		L->peeked = next_raw(L);
		L->has_peek = 1;
	}
	return (L->peeked);
}

static Token	lexer_next(Lexer *L)
{
	if (L->has_peek)
	{
		L->has_peek = 0;
		return (L->peeked);
	}
	return (next_raw(L));
}

static int	lexer_accept(Lexer *L, TokenKind k)
{
	if (lexer_peek(L).kind == k)
	{
		lexer_next(L);
		return (1);
	}		
	else
		return (0);
}

static void	free_token(Token t)
{
	if (t.kind == T_IDENT)
		free(t.text);
}

int	main(void)
{
	char	line[4096];
	Token	tk;
	Lexer	L;

	printf("pairs> ");
	while (fgets(line, sizeof line, stdin))
	{
		lexer_init(&L, line);
		while (1)
		{
			tk = lexer_next(&L);
			if (tk.kind == T_IDENT)
				printf("IDENT(\"%s\")\n", tk.text);
			else if (tk.kind == T_EQ)
				printf("EQ(=)\n");
			else if (tk.kind == T_SEMI)
				printf("SEMI(;)\n");
			else if (tk.kind == T_END)
			{
				printf("END\n");
				free_token(tk);
				break ;
			}
			else
				printf("ERR\n");
			free_token(tk);
		}
		printf("pairs> ");
	}
	return (0);
}