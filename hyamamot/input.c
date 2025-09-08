#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*line;

	line = NULL;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{ // line == NULLのときにfreeしたらsegmentation faultの可能性が。。。!
			free(line);
			break ;
		}
		printf("line is %s\n", line);
		add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}