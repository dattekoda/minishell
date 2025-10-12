/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:40:21 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/12 21:38:02 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


#include <stdlib.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "libft.h"

#define CWD_INIT_SIZE 4096

void	normal_minishell_exit(t_mini *mini, void (*func)(void *), \
	void *ptr, int status)
{
	if (func)
		(*func)(ptr);
	t_mini_free(mini);
	exit(status);
}

size_t	search_envp_i(t_mini *mini, char *arg, size_t var_len)
{
	size_t	i;

	i = 0;
	while (mini->envp[i])
	{
		if (!ft_strncmp(arg, mini->envp[i], var_len) \
			&& mini->envp[i][var_len] == '=')
			break ;
		i++;
	}
	return (i);
}

// allocate memory and
// get copied cwd's PATH
char	*mini_getcwd(void)
{
	char	*cwd;
	size_t	cwd_size;

	cwd_size = CWD_INIT_SIZE;
	cwd = malloc(sizeof(char) * cwd_size);
	while (cwd && !getcwd(cwd, cwd_size))
	{
		free(cwd);
		cwd_size *= 2;
		cwd = malloc(sizeof(char) * cwd_size);
	}
	return (cwd);
}

int	add_mini_len(t_mini *mini)
{
	char	**tmp;

	mini->envp_len++;
	if (mini->envp_len > mini->envp_size)
	{
		mini->envp_size *= 2;
		tmp = ft_calloc(mini->envp_size + 1, sizeof(char *));
		if (!tmp)
			return (ERR);
		ft_memmove(tmp, mini->envp, mini->envp_size / 2 * sizeof(char *));
		free(mini->envp);
		mini->envp = tmp;
	}
	return (SUCCESS);
}

void	safe_delete_heredoc_file(char **hd_name)
{
	if (!*hd_name)
		return ;
	unlink(*hd_name);
	free(*hd_name);
	*hd_name = NULL;
}
