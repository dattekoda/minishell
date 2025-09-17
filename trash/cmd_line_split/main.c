#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;
	memmove(argv[1] + strlen(argv[1]), argv[2], strlen(argv[2]) + 1);
	printf("%s\n", argv[1]);
	return 0;
}
