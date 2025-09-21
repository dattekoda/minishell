#include <stdlib.h>
#include "libft.h"
#include "status.h"
#include "minishell_err.h"

static int	valid_and(char *line);
static int	valid_quote(char *line, char type);

int	validate(char *line)
{
	if (valid_and(line))
		return (free(line), ERR);
	if (valid_quote(line, '\''))
		return (free(line), ERR);
	if (valid_quote(line, '\"'))
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
			return (put_syntax_err('&'), ERR);
		line = tmp + 2;
	}
	return (SUCCESS);
}

static int	valid_quote(char *line, char type)
{
	char	*left;
	char	*right;

	while (*line)
	{
		left = ft_strchr(line, type);
		if (!left)
			break ;
		right = ft_strchr(left + 1, type);
		if (!right)
			return (put_syntax_err(type), ERR);
		line = right + 1;
	}
	return (SUCCESS);
}
