/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamamot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 00:14:09 by hyamamot          #+#    #+#             */
/*   Updated: 2025/09/04 00:26:43 by hyamamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
	T_IDENT,
	T_EQ,   // =
	T_SEMI, // ;
	T_END,
	T_ERR,
}	TokenKind;

typedef struct
{
	TokenKind	kind;
	char		*text;
	const char	*lexeme_start; // エラー表示用
}	Token;

// Lexerは状態と先読み
typedef struct
{
	const char	*p;
	int			has_peek;
	Token		peeked;
}	Lexer;

typedef struct 
{
	char	*key;
	char	*val;
}	Pair;

typedef struct
{
	Pair	*data;
	size_t	len;
	size_t	cap;
}	PairVec;



// ヘルパー関数
static void	fatal(const char *msg)
{
	fprintf(stderr, "Fatal: %s\n", msg);
	exit(1);
}

// IDENT文字の判定
// READMEに文法が記述されている
// 最初の文字だけLetterになっている
static int	is_ident_start(int c)
{
	return (isalpha(c) || c == '_');
}

static int	is_ident_rest(int c)
{
	return (isalnum(c) || c == '_');
}

// IDENT を読み取り、mallocした値を返す
static char	*read_ident(const char *start, const char **endp)
{
	const char	*p;
	size_t		n;
	char		*s;

	p = start;
	if (!is_ident_start((unsigned char)*p))
		return (NULL);
	p++;
	while (is_ident_rest((unsigned char)*p))
		p++;
	n = (size_t)(p - start);
	s = (char *)malloc(n - 1);
	if (!s)
		fatal("oom");
	memcpy(s, start, n);
	s[n] = '\0';	
	return (s);
}

// 空白をスキップ
// Lexer型に対してisspaceみたいな
static void	skip_space(Lexer *L)
{
	while (*(L->p) == ' ' || *(L->p) == '\t')
		(L->p)++;
}




// 四則演算なら評価
// bashならコマンドの実行がここに当たる
static void	dump_pairs(const PairVec *v)
{
	size_t	i;

	printf("Parsed %zu pair(s):\n", v->len);
	i = 0;
	while (i < v->len)
	{
		printf("	- %s = %s\n", v->data[i].key, v->data[i].val);
		i++;
	}
}

int	main(void)
{
	char	line[4096];
	char	*p;
	Lexer	L;
	PairVec	v;

	printf("pairs> ");
	while (fgets(line, sizeof line, stdin))
	{
		p = line;
		while (*p)
			p++;
		if (!(*p))
		{
			printf("pairs> ");
			continue ;
		}
		lexer_init(&L, line); // 字句解析
		v = parse_pair(&L);   // 構文解析
		dump_pairs(&v);       // 単に表示
		vec_free(&v);
		printf("pairs> ");
	}
	printf("\nbye.\n");
	return (0);
}