#include "libft.h"
#include "status.h"
#include <unistd.h>

// set function's name
// and put msg to err_fileno like
// Error: malloc failed.\n
void	err_system_call(char *func)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(func, STDERR_FILENO);
	ft_putendl_fd(" failed.", STDERR_FILENO);
}

void	put_err(char type)
{
	ft_putstr_fd("syntax error: ", STDERR_FILENO);
	if (type == '&')
		ft_putendl_fd("you cannot use '&', job control function", STDERR_FILENO);
	else if (type == '\'')
		ft_putendl_fd("you need enclose with \'", STDERR_FILENO);
	else if (type == '\"')
		ft_putendl_fd("you need enclose with \"", STDERR_FILENO);
}
