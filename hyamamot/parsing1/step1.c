// 字句解析だけ
// lexer(字句解析器)
// lexerに文字列の状態を保持させて、lexerを見ることでtokenを作る

#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum e_token_kind
{
	T_NUMBER,
	T_PLUS,
	T_MINUS,
	T_STAR,
	T_SLASH,
	T_LPAREN,
	T_RPAREN,
	T_EOF,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	double			number; // NUMBERの時だけ有効
	int				pos;    // 表示用
}	t_token;

typedef struct s_lexer
{
	const char	*text;
	int			i;     // 現在の位置
	int			n;     // 全体の長さ
}	t_lexer;

// 責任の分散

// 今見ている文字を読む (観察)
static int	l_peek(t_lexer *lx)
{
	if (lx->i >= lx->n)
		return (EOF); // define -1;
	else
		return (lx->text[lx->i]);
}

// 実際に進める (消費)
// 現在の位置を返して進める。
// 返り値は読んだ文字かEOF(-1)
static int	l_adv(t_lexer *lx)
{
	int	ch;

	ch = l_peek(lx);
	if (ch != EOF)
		lx->i++;
	return (ch);
}

static void	l_skip_ws(t_lexer *lx)
{
	while (isspace(l_peek(lx)))
		l_adv(lx);
}

static t_token	next_token(t_lexer	*lx)
{
	int		start;
	int		ch;
	long	val;

	l_skip_ws(lx);
	start = lx->i;
	ch = l_peek(lx);
	if (ch == EOF)
		return ((t_token){T_EOF, 0.0, lx->i});
	if (isdigit(ch))
	{
		val = 0;
		while (isdigit(l_peek(lx)))
			val = val * 10 + (l_adv(lx) - '0');
		return ((t_token){T_NUMBER, (double)val, start});
	}

	// chには記号が入っていて、今見ている位置はその一つ先
	l_adv(lx);
	if (ch == '+')
		return ((t_token){T_PLUS, 0.0, start});
	else if (ch == '-')
		return ((t_token){T_MINUS, 0.0, start});
	else if (ch == '*')
		return ((t_token){T_STAR, 0.0, start});
	else if (ch == '/')
		return ((t_token){T_SLASH, 0.0, start});
	else if (ch == '(')
		return ((t_token){T_LPAREN, 0.0, start});
	else if (ch == ')')
		return ((t_token){T_RPAREN, 0.0, start});
	else
	{
		fprintf(stderr, "Unknown char '%c' at '%d'\n", ch, start);
		return ((t_token){T_EOF, 0.0, lx->i});
	}
}

// 表示用の便利関数
static const char	*tname(t_token_kind t)
{
	if (t == T_NUMBER)
		return ("NUMBER");
	else if (t == T_PLUS)
		return ("PLUS");
	else if (t == T_MINUS)
		return ("MINUS");
	else if (t == T_STAR)
		return ("STAR");
	else if (t == T_SLASH)
		return ("SLASH");
	else if (t == T_LPAREN)
		return ("LPAREN");
	else if (t == T_RPAREN)
		return ("RPAREN");
	else if (t == T_EOF)
		return ("EOF");
	return ("?");
}

int	main(void)
{
	const char	*samples[] = {"42", "31 + 4*5", "(1+2) / 3", NULL};
	int			s;
	t_lexer		lx;
	t_token		tok;

	s = 0;
	while (samples[s])
	{
		printf("Input: %s\n", samples[s]);
		// lx 初期化
		lx.text = samples[s];
		lx.i = 0;
		lx.n = (int)strlen(samples[s]);
		while (1)
		{
			tok = next_token(&lx);
			if (tok.kind == T_NUMBER)
				printf("	%-7s val=%g pos=%d\n", tname(tok.kind), tok.number, tok.pos);
			else
				printf("	%-7s pos=%d\n", tname(tok.kind), tok.pos);
			if (tok.kind == T_EOF)
				break ;
		}
		s++;
	}
}

/*
output例：

Input: 42
        NUMBER  val=42 pos=0
        EOF     pos=2
Input: 31 + 4*5
        NUMBER  val=31 pos=0
        PLUS    pos=3
        NUMBER  val=4 pos=5
        STAR    pos=6
        NUMBER  val=5 pos=7
        EOF     pos=8
Input: (1+2) / 3
        LPAREN  pos=0
        NUMBER  val=1 pos=1
        PLUS    pos=2
        NUMBER  val=2 pos=3
        RPAREN  pos=4
        SLASH   pos=6
        NUMBER  val=3 pos=8
        EOF     pos=9
*/