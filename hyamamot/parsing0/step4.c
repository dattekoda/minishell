// 一つのペアだけを作成する
// hoge=foo;
// 一応norminetteを意識

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_token_kind
{
	T_IDENT,
	T_EQ,
	T_SEMI,
	T_END,
	T_ERR,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	char			*text;			// IDENTの時だけmalloc
	const char		*lexeme_start;	// エラー表示用
}	t_token;

typedef struct s_lexer
{
	const char	*p;
	int			has_peek;
	t_token		peeked;
}	t_lexer;

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

// helper関数
static void	*safe_malloc(size_t n)
{
	void	*p;

	p = malloc(n);
	if (!p)
	{
		perror("malloc");
		exit(1);
	}
	return (p);
}

static int	is_ident_start(int c)
{
	return (isalpha((unsigned char)(c)) || c == '_');
}

static int	is_ident_rest(int c)
{
	return (isalnum((unsigned char)(c)) || c == '_');
}

static void	skip_space(t_lexer *lx)
{
	while (*lx->p == ' ' || *lx->p == '\t')
		lx->p++;
}

static char	*read_ident(const char *s, const char **endp)
{
	const char	*p;
	size_t		n;
	char		*text;

	p = s;
	while (!is_ident_start(*p))
		return (NULL);
	p++;
	while (is_ident_rest(*p))
		p++;
	n = (size_t)(p - s);
	text = safe_malloc(n + 1);
	memcpy(text, s, n);
	text[n] = '\0';
	*endp = p;
	return (text);
}

// lexer シリーズ

// lexerはToken をラップしているもの
static void	lexer_init(t_lexer *lx, const char *in)
{
	lx->p = in;
	lx->has_peek = 0;
	lx->peeked.kind = T_ERR;
	lx->peeked.text = NULL;
	lx->peeked.lexeme_start = NULL;
}

// lxの中にあるinput文字列を見て、新しいトークンを作成
// 文字列を消費して次に進める
static t_token	next_raw(t_lexer *lx)
{
	t_token			t;
	unsigned char	c;

	skip_space(lx);
	t.kind = T_ERR;
	t.text = NULL;
	t.lexeme_start = lx->p;
	c = (unsigned char)*lx->p;
	if (c == '\0' || c == '\n')
	{
		t.kind = T_END;
		return (t);
	}
	if (c == '=')
	{
		t.kind = T_EQ;
		lx->p++;
		return (t);
	}
	if (c == ';')
	{
		t.kind = T_SEMI;
		lx->p++;
		return (t);
	}
	if (is_ident_start(c))
	{
		t.text = read_ident(lx->p, &lx->p);
		t.kind = T_IDENT;
		return (t);
	}
	// どこにも引っかからな時はT_ERRのまま返す。
	return (t);
}

static t_token	lexer_peek(t_lexer *lx)
{
	if (!lx->has_peek)
	{
		lx->peeked = next_raw(lx);
		lx->has_peek = 1;
	}
	return (lx->peeked);
}

// next_raw + lx->has_peekにフラグが立っているのかを確認
static t_token	lexer_next(t_lexer *lx)
{
	t_token	t;

	if (lx->has_peek)
	{
		lx->has_peek = 0;
		return (lx->peeked);
	}
	t = next_raw(lx);
	return (t);
}

// 先読みしたTokenのkindがEQだったら、next_rawでtokenを作って
// has_peekを0にして先読みしたものを返す。
static int	lexer_accept(t_lexer *lx, t_token_kind k)
{
	if (lexer_peek(lx).kind == k)
	{
		(void)lexer_next(lx);
		return (1);
	}
	return (0);
}

static void	free_token(t_token t)
{
	if (t.kind == T_IDENT)
		free(t.text);
}

static void	parse_error(const char *meg, t_token t)
{
	(void)t;
	fprintf(stderr, "Parse error: %s\n", meg);
	exit(1);
}

static char	*parse_ident(t_lexer *lx)
{
	t_token	tk;

	tk = lexer_next(lx);
	printf("[DEBUG] %s\n", tk.text);
	if (tk.kind != T_IDENT)
		parse_error("expected <Ident>", tk);
	return (tk.text);
}

t_pair	parse_pair(t_lexer *lx)
{
	t_pair	p;

	p.key = parse_ident(lx);
	if (!lexer_accept(lx, T_EQ));
		// parse_error("expected '='", lexer_peek(lx));
	p.value = parse_ident(lx);
	return (p);
}


// main
int	main(void)
{
	char	line[4096];
	t_lexer	lx;
	t_pair	p;

	printf("input> ");
	if (!fgets(line, sizeof line, stdin))
		return (0);
	lexer_init(&lx, line);
	p = parse_pair(&lx);
	printf("PAIR: %s = %s\n", p.key, p.value);
	free(p.key);
	free(p.value);
	return (0);
}

// next_rawでtokenを作成しておいて、それが先読みかどうかのフラグを
// 一緒に持っておく。