#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// ほぼ、pwdの機能を実装できた。

#define BUFSIZE 4096

int	main(void)
{
	char	*buf;
	size_t	buf_size;

	buf_size = BUFSIZE;
	buf = malloc(sizeof(char) * buf_size);
	// パスがbufsizeバイト以上になるときにはエラー ERANGEを返す。
	while (!getcwd(buf, buf_size))
	{
		free(buf);
		buf_size *= 2;
		buf = malloc(sizeof(char) * buf_size);
	}
	printf("%s\n", buf);
	return (free(buf), 0);
}
