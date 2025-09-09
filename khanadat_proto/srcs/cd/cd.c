#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "builtin.h"
#include "libft.h"
// chdir
// closedir
// readdir
// opendir

char	*dir_join(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;

	join = ft_calloc(len1 + len2 + 2, sizeof(char));
	ft_memmove(join, s1, len1);
	join[len1] = '/';
	ft_memmove(join + len1 + 1, s2, len2);
	return (join);
}

int	cd(int argc, char *argv[], char *envp[])
{
	char	*tmp;
	char	*join;
	char	*home;
	int		i = -1;

	if (argc == 1)
	{
		while (envp[++i])
		{
			if (!strncmp(envp[i], "HOME=", 5))
				break ;
		}
		home = envp[i] + 5;
		if (!chdir(home))
			return (0);
	}
	else if (argc == 2)
	{
		if (!chdir(argv[1]))
			return (0);
		tmp = pwd();
		join = dir_join(tmp, argv[1]);
		free(tmp);
		ft_putstr_fd(join, 1);
		// そのディレクトリがあるかどうかを判別する。
		if (!chdir(join))
			return (free(join), 0);
		free(join);
		perror("malloc");
	}
	perror("cd");
	return (1);
}
