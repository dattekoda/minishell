#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
// readlineはget_next_line
// ただし、内部で動的にメモリを確保している。
// rl_clear_historyで確保した領域を削除する。
// int	main(void)
// {
// 	char	*line;

// 	while ((line = readline("$ ")) != NULL) {
// 		add_history(line);
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	clear_history();
// 	return (0);
// }

int	main(void)
{
	char	*line;
	int		gnl;

	while((gnl = ft_get_next_line(STDIN_FILENO, &line) > 0)) {
		printf("%s", line);
		free(line);
	}
	return (0);
}
