#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char *line;

	signal(SIGINT, sigint_handler);
	while ((line = readline("$ ")) != NULL) {
		free(line);
	}
	rl_clear_history();
	return (0);
}