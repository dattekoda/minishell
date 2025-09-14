#include <stddef.h>
#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	size_t	i;
	char	*shell_name;

	if (argc > 2)
		return (1);
	shell_name = ft_strchr(argv[0], '/') + 1;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHELL=", 6))
		{
			ft_putstr_fd("SHELL=", STDOUT_FILENO);
			ft_putendl_fd(shell_name, STDOUT_FILENO);
			i++;
			continue;
		}
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
