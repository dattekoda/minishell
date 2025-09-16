#include "libft.h"
#include "status.h"
#include <stdlib.h>

static int	valid_and(char *line);
static void	put_err(char a);

int	validate(char *line)
{
	if (valid_and(line))
		return (free(line), ERR);
	return (SUCCESS);
}

static int	valid_and(char *line)
{
	char	*tmp;

	while (*line)
	{
		tmp = ft_strchr(line, '&');
		if (!tmp)
			break ;
		if (*(tmp + 1) != '&')
			return (put_err('&'), ERR);
		line = tmp + 2;
	}
	return (SUCCESS);
}

static void	put_err(char a)
{
	ft_putstr_fd("syntax error: ", STDERR_FILENO);
	if (a == '&')
		ft_putendl_fd("you cannot use '&', job control function", STDERR_FILENO);
}
