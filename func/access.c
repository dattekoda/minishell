#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	access(NULL, F_OK);
	perror("access");
}
