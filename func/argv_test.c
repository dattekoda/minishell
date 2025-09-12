#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	size_t	argv0_len = strlen(argv[0]);
	size_t	argv1_len = strlen(argv[1]);
	write(1, argv[0], argv0_len + argv1_len + 1);
	return (0);
}