/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 15:17:21 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "libft.h"
#include "get_path.h"
#include "ast.h"
#include "set_redirect.h"
#include "builtin.h"
#include "exec_utils.h"

void	exec_prompt(t_mini *mini, t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_OR)
	{
		exec_prompt(mini, node->lhs);
		if (!ft_strcmp("0", mini->status))
			return ;
		if (!ft_strcmp("130", mini->status))
			return ;
		exec_prompt(mini, node->rhs);
	}
	else if (node->kind == ND_AND)
	{
		exec_prompt(mini, node->lhs);
		if (ft_strcmp("0", mini->status))
			return ;
		exec_prompt(mini, node->rhs);
	}
	else
		exec_node(mini, node);
}

// int	set_abs_path(char **dir)
// {
// 	size_t	i;
// 	size_t	dir_len;
// 	size_t	pwd_len;
// 	char	*abs_path;
// 	char	*pwd;

// 	if (**dir == '/')
// 	{
// 		*dir = ft_strdup(*dir);
// 		if (!*dir)
// 			return (ERR);
// 		return (SUCCESS);
// 	}
// 	dir_len	= ft_strlen(*dir);
// 	pwd = mini_getcwd();
// 	pwd_len = ft_strlen(pwd);
// 	abs_path = ft_calloc(dir_len + pwd_len + 2, sizeof(char));
// 	if (!abs_path)
// 		return (ERR);
// 	i = 0;
// 	ft_memmove(abs_path + i, pwd, pwd_len);
// 	i += pwd_len;
// 	ft_memmove(abs_path + i, "/", 1);
// 	i += 1;
// 	ft_memmove(abs_path + i, *dir, dir_len);
// 	*dir = abs_path;
// 	return (SUCCESS);
// }
