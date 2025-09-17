#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "tokenizer.h"
#include "status.h"

// abstruct syntax tree
typedef struct s_node
{
	char			**argv;
	char			*str;
	struct s_node	*lhs;
	struct s_node	*rhs;
	TokenKind		kind;
}	t_node;

int	main(int argc, char *argv[]) {
	char	*line;
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (1) {
		line = readline("$ ");
		add_history(line);
		if (validate(line))
			return (FAILURE);
		if (get_token(&cur, line))
			return (free(line), FAILURE);
		free(line);
		free_token(cur->next);
	}
	rl_clear_history();
	return (SUCCESS);
}
