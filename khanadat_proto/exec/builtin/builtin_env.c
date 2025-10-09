/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:49:42 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 15:16:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"

#include "libft.h"

void	exec_env(t_mini *mini, char **argv)
{
	size_t	i;

	if (argv[1])
	{
		err_msg_env(argv[1]);
		store_status(FAILURE, mini);
		return ;
	}
	i = 0;
	while (i < mini->envp_len)
		ft_putendl_fd(mini->envp[i++], STDOUT_FILENO);
	store_status(SUCCESS, mini);
}
