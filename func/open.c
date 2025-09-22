#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	struct stat	buf;
	stat(argv[1], &buf);
	if (S_ISREG(buf.st_mode))
		printf("this is normal file\n");
	else if (S_ISDIR(buf.st_mode))
		printf("this is directory\n");
}