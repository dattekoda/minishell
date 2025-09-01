#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 20

int	main(void)
{
	char	buf[BUFSIZE];

	// パスがbufsizeバイト以上になるときにはエラー ERANGEを返す。
	if (getcwd(buf, BUFSIZE))
		printf("%s\n", buf);
}