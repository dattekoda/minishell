/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:51:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/04 22:53:16 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell_lib.h"
#include "ast.h"

static char	*get_program_name(char *set);

void	mini_safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	t_mini_free(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (i < mini->envp_len)
	{
		if (mini->envp[i])
			free(mini->envp[i]);
		i++;
	}
	free(mini->envp);
	mini_safe_free((void **)&mini->line);
	free_node(&mini->node);
	rl_clear_history();
}

// caution: the name should
// set only once throughout
// the program.
// set char *set NULL then
// you can get program_name
// set's len exceeds FILENAME_MAX
// then return NULL
char	*access_program_name(char *set)
{
	static char	name[FILENAME_MAX];
	char		*actual_name;

	if (!set)
		return (name);
	actual_name = get_program_name(set);
	if (FILENAME_MAX < ft_strlen(actual_name))
		return (ft_putstr_fd(actual_name, STDERR_FILENO), \
		ft_putendl_fd(": File name too long", STDERR_FILENO), NULL);
	ft_strlcpy(name, actual_name, FILENAME_MAX);
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
		mini_safe_free((void **)&splited[i++]);
	mini_safe_free((void **)&splited);
}
