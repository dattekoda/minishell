#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// chdir
// closedir
// readdir
// opendir

#define BUFSIZE 64

char	*pwd(void)
{
	char	*buf;
	size_t	buf_size;

	buf_size = BUFSIZE;
	buf = malloc(sizeof(char) * buf_size);
	// パスがbufsizeバイト以上になるときにはエラー ERANGEを返す。
	while (buf && !getcwd(buf, buf_size))
	{
		free(buf);
		buf_size *= 2;
		buf = malloc(sizeof(char) * buf_size);
	}
	return (buf);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1 = strlen(s1);
	size_t	len2 = strlen(s2);
	char	*join = calloc(len1 + len2 + 1, sizeof(char));

	if (!join)
		return (NULL);
	memmove(join, s1, len1);
	return (memmove(join, s2, len2));
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
		printf("%s", home);
		if (!chdir(home))
			return (0);
	}
	else if (argc == 2)
	{
		if (!chdir(argv[1]))
			return (0);
		tmp = pwd();
		join = ft_strjoin(tmp, argv[1]);
		free(tmp);
		if (!chdir(join))
			return (free(join), 0);
		free(join);
		perror(malloc);
	}
	perror("cd");
	return (1);
}
