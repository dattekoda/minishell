#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

#define FILENAME_DAFAULT_LEN 13

char	*set_heredoc_name(void)
{
	static unsigned int	num = 0;
	static char			file_name[FILENAME_MAX];
	int					tmp;
	int					i;

	tmp = num;
	ft_strlcpy(file_name, "/tmp/.heredoc", FILENAME_MAX);
	i = FILENAME_DAFAULT_LEN;
	if (tmp == 0)
		file_name[i++] = '0';
	while (tmp)
	{
		file_name[i++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	file_name[i] = '\0';
	num++;
	if (!access(file_name, F_OK))
		return (set_heredoc_name());
	return (file_name);
}

int	main(void)
{
	for (int i = 0; i < 100; i++)
		printf("%s\n", set_heredoc_name());
	return (0);
}
