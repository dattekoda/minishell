#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "libft.h"
#include "status.h"
#include "minishell_err.h"
#include "tokenizer.h"
#include "ast_define.h"
#include "ast_utils.h"

int	get_node(t_node **node, t_token *token)
{
	t_node	*cur;

	cur = pipe_node(&token);
	*node = cur;
	while (cur)
	{
		if (consume(&token, TK_OR))
			cur = new_node(ND_OR, cur, pipe_node(&token));
		else if (consume(&token, TK_AND))
			cur = new_node(ND_AND, cur, pipe_node(&token));
		else
			break ;
	}
	if (!cur)
		return (ERR);
	*node = cur;
	return (SUCCESS);
}

void	free_node(t_node *node)
{
	size_t	i;

	if (!node)
		return ;
	free_node(node->lhs);
	free_node(node->rhs);
	if (node->kind == ND_CMD)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
	}
	free(node);
	node = NULL;
}

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->kind == TK_AND)
			printf("AND\n");
		else if (token->kind == TK_OR)
			printf("OR\n");
		else if (token->kind == TK_PIPE)
			printf("PIPE\n");
		else if (token->kind == TK_WORD)
			printf("WORD\n");
		token = token->next;
	}
}

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
	t_token	head;
	t_token	*cur;
	t_node	*node;

	cur = &head;
	while (1) {
		ft_bzero(&head, sizeof(t_token));
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if (get_token(cur, line))
			return (free(line), free_token(cur->next), FAILURE);
		// print_token(cur->next);
		if (get_node(&node, cur->next))
			return (free_node(node), free_token(cur->next), free(line), FAILURE);
		print_node(node);
		free_node(node);
		free_token(cur->next);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}
