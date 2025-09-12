// parserは状態を一箇所にまとめるだけの器

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
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
	double			val;
	int				pos;
}	t_token;

typedef struct s_lexer
{
	const char	*text;
	int			i;
	int			n;
}	t_lexer;

typedef struct s_parser
{
	t_lexer	lx;
	t_token	cur;
}	t_parser;

static double	parse_all(const char *s)
{

}

int	main(void)
{
	const char	*tests[] = {"42", "3+4*5", "10/2/5", "8-3*2+1", NULL};
	int			i;

	i = 0;
	while (tests[i])
	{
		printf("%s => %g\n", tests[i], parse_all(tests[i]));
		i++;
	}
	return (0);
}