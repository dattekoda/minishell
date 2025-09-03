#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int	count;

void	signal_handler(int signum)
{
	count += 100;
}

int	main(void)
{
	struct sigaction	sa;

	if (-1 == sigemptyset(&sa.sa_mask))
		exit(1);
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;

	if (-1 == sigaction(SIGINT, &sa, NULL))
		exit(1);
	while (count < 50) {
	};

	puts("Count Over");	
	return (0);
}
