/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:49:42 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"

#include "libft.h"

void	exec_env(t_mini *mini, char **argv, bool exp)
{
	size_t	i;

	if (argv[1])
	{
		err_msg_env(argv[1]);
		store_status(FAILURE, mini);
		return ;
	}
	i = 0;
	while (exp && i < mini->envp_len)
	{
		if (ft_strncmp("_=", mini->envp[i], 2))
			ft_putendl_fd(mini->envp[i], STDOUT_FILENO);
		i++;
	}
	while (!exp && i < mini->envp_len)
	{
		if (ft_strchr(mini->envp[i], '='))
			ft_putendl_fd(mini->envp[i], STDOUT_FILENO);
		i++;
	}
	store_status(SUCCESS, mini);
}
