#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include "libft.h"
#include "status.h"
#include "minishell_err.h"

int	main(int argc, char *argv[])
{
	size_t	i = 0;

	if (argc == 1)
		return FAILURE;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i], '<'))
		{
			if (!argv[i + 1])
				
		}
	}
	return (SUCCESS);
}