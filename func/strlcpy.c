#include "libft.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	char	buffer[PATH_MAX];

	if (argc != 3)
		return 1;
	ft_strlcpy(buffer, argv[1], 3);
	ft_strlcat(buffer, argv[2], ft_strlen(buffer) + 3 + 1);
	printf("%s\n", buffer);
	return 0;
}