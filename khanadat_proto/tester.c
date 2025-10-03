#include <stdio.h>
#include "ast.h"
#include "expand_define.h"

void	check_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		fprintf(stderr, "%s\n", argv[i]);
		i++;
	}
}

void	check_word(t_word *word)
{
	while (word)
	{
		fprintf(stderr, "%s ", word->word);
		word = word->next;
	}
	fprintf(stderr, "\n");
}

void	dol_checker(t_dollar *dol)
{
	while (dol)
	{
		if (dol->dkind == WD_WORD)
		{
			fprintf(stderr, "val:	%s\n", dol->value);
			fprintf(stderr, "len:	%zu\n", dol->value_len);
		}
		else if (dol->dkind == WD_SPACE)
			fprintf(stderr, "space\n");
		fprintf(stderr, "\n");
		dol = dol->next;
	}
}

void	print_node(t_node *node)
{
	t_red	*r;
	t_word	*w;

	if (node->lhs)
		print_node(node->lhs);
	if (node->kind == ND_AND)
		printf("and\n");
	else if (node->kind == ND_OR)
		printf("or\n");
	else if (node->kind == ND_PIPE)
		printf("pipe\n");
	else if (node->kind == ND_CMD)
	{
		printf("cmd: ");
		w = node->word;
		while (w)
		{
			printf("%s ", w->word);
			w = w->next;
		}
		printf("\n");
		r = node->red;
		while (r)
		{
			if (r->kind == RD_APPEND)
				printf("append: ");
			else if (r->kind == RD_HEREDOC)
				printf("heredoc: ");
			else if (r->kind == RD_IN)
				printf("redirect in: ");
			else if (r->kind == RD_OUT)
				printf("redirect_out: ");
			printf("%s\n", r->file);
			r = r->next;
		}
	}
	if (node->rhs)
		print_node(node->rhs);
}
