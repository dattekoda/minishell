/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:13:22 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 13:16:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "status.h"
#include "minishell_lib.h"

static void	put_syntax_err(char a);

int	valid_quote(char *line)
{
	char	*tmp;

	while(*line)
	{
		if (*line != '\'' && *line != '\"')
		{
			line++;
			continue ;
		}
		if (*line == '\'')
			tmp = ft_strchr(line + 1, '\'');
		else if (*line == '\"')
			tmp = ft_strchr(line + 1, '\"');
		if (!tmp)
			return (put_syntax_err(*line), ERR);
		line = tmp + 1;
	}
	return (SUCCESS);
}

// set access_program_name before using this function
static void	put_syntax_err(char a)
{
	ft_putstr_fd(access_program_name(NULL), STDERR_FILENO);
	ft_putstr_fd(": syntax error: ", STDERR_FILENO);
	if (a == '\'')
		ft_putendl_fd("you need enclose with \'", STDERR_FILENO);
	else if (a == '\"')
		ft_putendl_fd("you need enclose with \"", STDERR_FILENO);
}
