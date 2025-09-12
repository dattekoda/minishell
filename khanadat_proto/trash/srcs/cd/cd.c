#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "builtin.h"
#include "libft.h"

// chdir
// closedir
// readdir
// opendir


static char	*get_absolute_dir(char *dir);
static void	msg_err_cd(char *dir_name);

int	builtin_cd(int argc, char *argv[], char *home)
{
	char	*absolute_path;

	if (argc == 1)
	{
		if (!chdir(home))
			return (0);
	}
	else if (2 <= argc)
	{
		// absolute_path = get_absolute_dir(argv[1]);
		if (!chdir(argv[1]))
			return (0);
		msg_err_cd(argv[1]);
	}
	return (1);
}

// 結局使わなかった。
static char	*get_absolute_dir(char *dir)
{
	size_t	len_cwd;
	size_t	len_dir;
	char	*cwd;
	char	*relative_dir;

	cwd = pwd();
	if (!cwd)
		return (NULL);
	len_cwd = ft_strlen(cwd);
	len_dir = ft_strlen(dir);
	relative_dir = ft_calloc(len_cwd + len_dir + 2, sizeof(char));
	if (!relative_dir)
		return (free(cwd), NULL);
	ft_memmove(relative_dir, cwd, len_cwd);
	relative_dir[len_cwd] = '/';
	ft_memmove(relative_dir + len_cwd + 1, dir, len_dir);
	return (free(cwd), relative_dir);
}

static void	msg_err_cd(char *dir_name)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(dir_name, STDERR_FILENO);
}
