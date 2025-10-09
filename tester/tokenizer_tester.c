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
	int		status;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		status = get_token(&token, line);
		if (status == ERR)
			return (free(line), FAILURE);
		if (status == SYNTAX_ERR)
		{
			free(line);
			continue ;
		}
		print_token(token);
		free_token(&token);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}

static void	print_token(t_token *token)
{
	while (token)
	{
		if (token->kind == TK_OPERATOR)
			printf("OPERATOR\n");
		else if (token->kind == TK_WORD)
			printf("WORD\n");
		else if (token->kind == TK_EOF)
			printf("EOF\n");
		token = token->next;
	}
}
