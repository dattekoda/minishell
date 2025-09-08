#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	int		i;
	bool	first;
	bool	no_nl;

	no_nl = false;
	if (argc != 1)
	{
		no_nl = (strcmp(argv[1], "-n") == 0);
		i = (no_nl); // no_nl==true then 1 else 0
		first = true;
		while (++i < argc)
		{
			if (!first)
				printf(" ");
			first = false;
			printf("%s",argv[i]);
		}
	}
	if (!no_nl)
		printf("\n");
	return (0);
}