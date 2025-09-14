#include <unistd.h>
#include <stdio.h>
#include "libft.h"

size_t	count_path(const char *envp_home)
{
	char	*chr;
	size_t	count;

	chr = ft_strchr(envp_home, ':');
	count = 1;
	while (chr)
	{
		count++;
		*chr = '\0';
		chr = ft_strchr(chr + 1, ':');
	}
	return (count);
}

int	set_path(char *path_dup, char ***env_path)
{
	size_t	count;
	size_t	i;

	count = count_path(path_dup);
	*env_path = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!*env_path)
		return (-1);
	i = 0;
	while (i < count)
	{
		(*env_path)[i++] = path_dup;
		path_dup += ft_strlen(path_dup) + 1;
	}
	return (0);
}

int	exec_cmd(int argc, char *argv[], char *envp[])
{
	char	**env_argv;
	char	*path_dup;
	char	*path;
	char	*slash;
	size_t	i;
	pid_t	p;
	int		status;

	if (argc == 1)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (1);
	path_dup = ft_strdup(envp[i] + 5);
	if (!path_dup)
		return (1);
	if (set_path(path_dup, &env_argv))
		return (free(path_dup), 1);
	slash = ft_strjoin("/", argv[1]);
	if (!slash)
		return (free(env_argv), free(path_dup), 1);
	i = 0;
	while (env_argv[i])
	{
		path = ft_strjoin(env_argv[i++], slash);
		if (!path)
			return (free(env_argv), free(path_dup), free(slash), 1);
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
	}
	free(slash);
	if (!env_argv[i])
		exit((free(env_argv), free(path_dup), 127));
	p = fork();
	if (p == 0)
		execve(path, &argv[1], envp);
	if (waitpid(p, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	return (free(env_argv), free(path_dup), status);
}

int	main(int argc, char *argv[], char *envp[])
{
	return (exec_cmd(argc, argv, envp));
}