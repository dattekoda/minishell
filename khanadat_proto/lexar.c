#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
// #include "expand.h"

#define TYPE_COMMAND 1
#define TYPE_OPERAND 2
#define TYPE_PIPE 3

typedef enum
{
	ND_PIPE,
	ND_INRED, // < input redirect
	ND_OUTRED, // > output redirect
	ND_HD, // << here_doc
	ND_APRED, // >> append redirect
	ND_SPACE,
	ND_CMD,
	ND_WORD,
	ND_SINGLE, // '
	ND_DOUBLE // "
}	NodeKind;

typedef struct s_cmd
{
	char			*cmd;
	int				argc;
	char			**argv;
	char			*path;
}	t_cmd;

int	main(void)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		expanded = NULL;
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		free(expanded);
	}
	rl_clear_history();
	return (0);
}
