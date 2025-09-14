
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "expand.h"

int	main(void)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if (expand_params(line, &expanded))
			continue ;
		printf("%s\n", expanded);
		free(expanded);
	}
	rl_clear_history();
	return (SUCCESS);
}
