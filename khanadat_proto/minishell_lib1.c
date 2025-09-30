/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:51:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 09:44:18 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include "minishell_lib.h"

static char	*get_program_name(char *set);

void	safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	free_program_name(void)
{
	access_program_name \
	("free_program_name");
}

// set char *set "free_program_name" then
// you can free static char*
char	*access_program_name(char *set)
{
	static char	*name = NULL;

	if (set && name \
		&& !ft_strcmp(set, "free_program_name"))
	{
		safe_free((void **)&name);
		return (NULL);
	}
	if (!name)
		name = ft_strdup(get_program_name(set));
	if (!name)
		return (ft_putstr_fd(set, STDERR_FILENO), \
		ft_putendl_fd(": Error: malloc failed", STDERR_FILENO), \
		NULL);
	return (name);
}

static char	*get_program_name(char *set)
{
	char	*program_name;
	char	*tmp;

	program_name = ft_strchr(set, '/');
	if (!program_name)
		program_name = set;
	else
	{
		tmp = program_name;
		while (1)
		{
			program_name = ft_strchr(tmp + 1, '/');
			if (!program_name)
				break ;
			tmp = program_name;
		}
		program_name = tmp + 1;
	}
	return (program_name);
}

void	free_split(char **splited)
{
	size_t	i;

	i = 0;
	while (splited[i])
		safe_free((void **)&splited[i++]);
	safe_free((void **)&splited);
}
