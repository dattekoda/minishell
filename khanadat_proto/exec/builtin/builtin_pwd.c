/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:35:22 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:50 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "libft.h"

void	exec_pwd(t_mini *mini, char **argv)
{
	char	*cwd;

	cwd = mini_getcwd();
	if (!cwd)
	{
		free(argv);
		systemcall_minishell_exit(mini, "malloc");
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	store_status(0, mini);
}
