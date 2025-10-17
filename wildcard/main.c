#include "libft.h"
#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// case : Not clearly sep
void	err_wc_syntax(void)
{
	ft_putstr_fd("syntax error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// case : Contains invalid char
void	err_wc_malicious(char *mes)
{
	ft_putstr_fd(mes, STDERR_FILENO);
	ft_putstr_fd("malicious err\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

bool	is_wildcard(char *arg, char *file)
{
	if (!*arg)
		return (!*file);
	if (*arg == '*')
	{
		while (*arg == '*')
			arg++;
		if (!*arg)
			return (true);
		while (*file)
		{
			if (is_wildcard(arg, file))
				return (true);
			file++;
		}
	}
	if (*file && *arg == *file)
		return (is_wildcard(arg + 1, file + 1));
	return (false);
}

int	main(int argc, char *argv[])
{
	DIR				*dir_ptr;
	struct dirent	*dirent_ptr;

	if (argc == 1)
		return (1);
	if (!ft_strchr(argv[1], '*'))
		return (0);
	if (argv[2])
	{
		dprintf(0, "if (argv[2])\n");
		dir_ptr = opendir(argv[2]);
	}
	else
		dir_ptr = opendir(".");
	if (!dir_ptr)
		perror("opendir");
	while (1)
	{
		dirent_ptr = readdir(dir_ptr);
		if (!dirent_ptr)
			break ;
		if ((*argv[1] != '.' && *dirent_ptr->d_name == '.') || !ft_strcmp("..",
				dirent_ptr->d_name) || !ft_strcmp(".", dirent_ptr->d_name))
			continue ;
		if (is_wildcard(argv[1], dirent_ptr->d_name))
			printf("%s\n", dirent_ptr->d_name);
	}
	closedir(dir_ptr);
	return (0);
}
