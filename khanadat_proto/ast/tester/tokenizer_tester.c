#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "tokenizer_define.h"
#include "tokenizer.h"
#include "status.h"

static void	print_token(t_token *token);

int	main(void)
{
	char	*line;
	t_token	*token;

	while (1)
	{
		token = NULL;
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if (get_token(&token, line))
			return (free(line), FAILURE);
		print_token(token);
		free_token(token);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}

static void	print_token(t_token *token)
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
		else if (token->kind == TK_EOF)
			printf("EOF\n");
		token = token->next;
	}
}