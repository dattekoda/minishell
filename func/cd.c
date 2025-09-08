#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
// chdir
// closedir
// readdir
// opendir

int	main(int argc, char *argv[])
{
	DIR	*stream;

	stream = opendir(argv[1]);
	if (stream)
	{
		
	}
}