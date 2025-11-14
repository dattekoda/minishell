/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:13:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell_define_bonus.h"
#include "builtin_utils_bonus.h"
#include "libft.h"

bool	exec_builtin(t_mini *mini, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (exec_cd(mini, cmd->argv), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (exec_echo(mini, cmd->argv), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (exec_env(mini, cmd->argv, false), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (exec_exit(mini, cmd->argv), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (exec_export(mini, cmd->argv), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (exec_pwd(mini), \
		cmd->pid = PID_BUILTIN, true);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (exec_unset(mini, cmd->argv), \
		cmd->pid = PID_BUILTIN, true);
	return (false);
}
