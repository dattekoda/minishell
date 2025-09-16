#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

int	main(int argc, char *argv[]) {
	char	*line;

	while (1) {
		line = readline("$ ");
		
		free(line);
	}
}
