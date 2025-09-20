#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "ast_define.h"
#include "ast.h"
#include "tokenizer_define.h"
#include "tokenizer.h"
#include "status.h"

void	print_node(t_node *node)
{
	char	**v;
	t_red	*r;

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
		v = node->argv;
		while (*v)
			printf("%s ", *(v++));
		printf("\n");
		r = node->red;
		while (r)
		{
			if (r->kind == ND_APPEND)
				printf("append: ");
			else if (r->kind == ND_HEREDOC)
				printf("heredoc: ");
			else if (r->kind == ND_RED_IN)
				printf("redirect in: ");
			else if (r->kind == ND_RED_OUT)
				printf("redirect_out: ");
			printf("%s\n", r->file);
			r = r->next;
		}
	}
	if (node->rhs)
		print_node(node->rhs);
}

int	main(void) {
	char	*line;
	t_token	*token;
	t_node	*node;
	int		status;

	while (1) {
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		status = get_token(&token, line);
		if (status < 0)
			return (free(line), FAILURE);
		if (status == SYNTAX_ERR)
		{
			free(line);
			continue ;
		}
		status = get_node(&node, token);
		if (status < 0)
			return (free_token(token), free(line), FAILURE);
		if (status == SYNTAX_ERR)
		{
			free_token(token);
			free(line);
			continue ;
		}
		print_node(node);
		free_node(node);
		free_token(token);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}
