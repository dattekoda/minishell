#include "libft.h"
#include "status.h"
#include "expand.h"

static void	put_err(char a);

// 'hello' > hello hello"$HOME" > hello/home/khanadat
int	expand_quotation(char *before, char **new)
{
	char	*tmp;

	tmp = NULL;
	while (*before)
	{
		if (*before != '\'' || *before != '\"')
		{
			before++;
			continue ;
		}
		tmp = ft_strchr(before + 1, *before);
		if (!tmp)
			return (put_error(*before), ERR);
		before = tmp + 1;
	}
}

static void	put_err(char asc)
{
	ft_putstr_fd("syntax error: ", STDERR_FILENO);
	if (asc == '\'')
		ft_putendl_fd("you need enclose with \'", STDERR_FILENO);
	else if (asc == '\"')
		ft_putendl_fd("you need enclose with \"", STDERR_FILENO);
}