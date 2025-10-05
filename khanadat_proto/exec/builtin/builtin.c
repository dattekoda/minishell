/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:13:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 18:19:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell_define.h"
#include "builtin_utils.h"
#include "libft.h"

bool	exec_builtin(t_mini *mini, char **argv)
{
	if (!ft_strcmp(argv[0], "cd"))
		return (exec_cd(mini, argv), true);
	if (!ft_strcmp(argv[0], "echo"))
		return (exec_echo(mini, argv), true);
	if (!ft_strcmp(argv[0], "env"))
		return (exec_env(mini, argv), true);
	if (!ft_strcmp(argv[0], "exit"))
		return (exec_exit(mini, argv), true);
	if (!ft_strcmp(argv[0], "export"))
		return (exec_export(mini, argv), true);
	if (!ft_strcmp(argv[0], "pwd"))
		return (exec_pwd(mini, argv), true);
	if (!ft_strcmp(argv[0], "unset"))
		return (exec_unset(mini, argv), true);
	return (false);
}
