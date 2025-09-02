#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int	count;

// シグナル安全のためprintfは良くない
void	signal_handler(int signum)
{
	printf("中止！\n");
	exit(1);
}

int	main(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	while (1){		
	};
	return (0);
}
