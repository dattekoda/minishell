#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include "libft.h"
#include "tokenizer.h"
#include "status.h"

static void	print_token(t_token *token);

int	main(void) {
	char	*line;
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (1) {
		line = readline("> ");
		if (!line)
			break ;
		add_history(line);
		if (validate(line))
			continue ;
		if (get_token(&cur, line))
			return (free(line), 1);
		print_token(cur->next);
		free(line);
		free_token(cur->next);
	}
	rl_clear_history();
	return (SUCCESS);
}

static void	print_token(t_token *token)
{
	while (token)
	{
		if (token->kind == TK_WORD)
			printf("word: %s\n", token->str);
		else if (token->kind == TK_APPEND)
			printf("double: %s\n", token->str);
		else if (token->kind == TK_HERE_DOC)
			printf("here_doc\n");
		else if (token->kind == TK_PIPE)
			printf("pipe\n");
		else if (token->kind == TK_REDIR_IN)
			printf("in\n");
		else if (token->kind == TK_REDIR_OUT)
			printf("out\n");
		else if (token->kind == TK_AND)
			printf("and\n");
		else if (token->kind == TK_OR)
			printf("or\n");
		token = token->next;
	}
	printf("eof\n");
}
