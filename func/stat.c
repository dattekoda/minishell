#include <sys/stat.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	struct stat	buf;
	stat(argv[1], &buf);
	if (S_ISDIR(buf.st_mode))
		printf("dir\n");
	else if (S_ISREG(buf.st_mode))
		printf("file\n");
	else if (S_ISLNK(buf.st_mode))
		printf("link\n");
	else
		printf("not dir\n");
	return 0;
}
