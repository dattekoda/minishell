/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:37:46 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 11:54:57 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "minishell_define.h"
#include "libft.h"

// found var then return value
// else return NULL
char	*normal_getenv(char *var, t_mini *mini)
{
	size_t	len;
	size_t	i;
	char	*chr;

	len = ft_strlen(var);
	i = 0;
	while (i < mini->envp_len)
	{
		if (!ft_strncmp(var, mini->envp[i], len) \
		&& mini->envp[i][len] == '=')
			break ;
		i++;
	}
	if (!mini->envp[i])
		return (NULL);
	chr = ft_strchr(mini->envp[i], '=');
	if (chr)
		return (chr + 1);
	return (NULL);
}

// status span the range of 0-255
void	store_status(int status, t_mini *mini)
{
	size_t	behind;

	ft_bzero(mini->status, STATUS_SIZE);
	if (status == 0)
	{
		mini->status[0] = '0';
		return ;
	}
	if (status < 10)
		behind = 0;
	else if (status < 100)
		behind = 1;
	else
		behind = 2;
	while (status)
	{
		mini->status[behind--] = status % 10 + '0';
		status /= 10;
	}
}
