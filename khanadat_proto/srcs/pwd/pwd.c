#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#define BUFSIZE 64

// NULL might be included
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

void	print_pwd(void)
{
	char	*pwd_str;

	pwd_str = pwd();
	if (!pwd_str)
		return ;
	ft_putendl_fd(pwd_str, STDOUT_FILENO);
	free(pwd_str);
}

// int	main(void)
// {
// 	print_pwd();
// }
