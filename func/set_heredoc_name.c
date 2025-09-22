#include <stdio.h>
#include "libft.h"
#define HEREDOC_NAME_SIZE_MAX 10

int	set_heredoc_name(char **heredoc_name)
{
	static unsigned int	name = 0;
	char				buffer[HEREDOC_NAME_SIZE_MAX + 1];
	int					tmp;
	int					i;

	buffer[HEREDOC_NAME_SIZE_MAX] = '\0';
	if (*heredoc_name)
		free(*heredoc_name);
	*heredoc_name = NULL;
	tmp = name;
	i = HEREDOC_NAME_SIZE_MAX;
	if (tmp == 0)
		buffer[--i] = '0';
	while (tmp)
	{
		buffer[--i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	*heredoc_name = ft_strjoin("/tmp/.heredoc", &buffer[i]);
	if (!*heredoc_name)
		return (1);
	name++;
	if (!access(*heredoc_name, F_OK))
		return (set_heredoc_name(heredoc_name));
	return (0);
}

int	main(void)
{
	char	*name;

	name = NULL;
	for (int i = 0; i < 10; i++) {
		set_heredoc_name(&name);
		printf("%s\n", name);
	}
	return (0);
}
