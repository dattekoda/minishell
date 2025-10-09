/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:32:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 15:16:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "minishell_define.h"
#include "minishell_lib.h"

#include "libft.h"

void	exec_unset(t_mini *mini, char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (argv[++i])
	{
		j = search_envp_i(mini, argv[i], ft_strlen(argv[i]));
		if (!mini->envp[j])
			continue ;
		free(mini->envp[j]);
		ft_memmove(mini->envp + j, mini->envp + j + 1, \
			(mini->envp_len - j) * sizeof(char *));
		(mini->envp_len)--;
	}
	store_status(SUCCESS, mini);
}
