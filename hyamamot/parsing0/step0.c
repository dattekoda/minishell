#include <stdio.h>

int	main(void)
{
	char	line[4096];

	printf("pairs> ");
	while (fgets(line, sizeof line, stdin))
	{
		printf("[ECHO] %s\n", line);
		printf("pairs> ");
	}
	return (0);
}