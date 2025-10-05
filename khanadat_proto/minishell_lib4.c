/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 00:40:21 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 16:35:37 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"

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
