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
		v = node->argv;
		printf("cmd: ");
		while (*v)
			printf("%s ", *(v++));
		printf("\n");
	}
	if (node->rhs)
		print_node(node->rhs);
}

int	main(void) {
	char	*line;
	t_token	*token;
	t_node	*node;

	while (1) {
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if (get_token(&token, line))
			return (free(line), FAILURE);
		if (get_node(&node, token))
			return (free_token(token), free(line), FAILURE);
		print_node(node);
		free_node(node);
		free_token(token);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}
