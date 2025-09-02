#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static volatile sig_atomic_t g_sigint = 0;

static void	on_sigint(void) {
	g_sigint = 1;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	install_handler(int sig, void (*handler)(int)) {
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}
}

int	main(void)
{
	char *line = NULL;

	install_handler(SIGINT, on_sigint);
	while (1)
	{
		line = readline("> ");
		if (line == NULL) {
			printf("exit\n");
			break;
		}
		if (*line == '\0') {
			free(line);
			continue;
		}
		if (strcmp(line, "exit") == 0) {
			free(line);
			printf("exit\n");
			break;
		}
		printf("line is %s\n", line);
		add_history(line);
		free(line);
		g_sigint = 0;
	}
	return 0;
}
