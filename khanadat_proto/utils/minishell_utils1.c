/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:51:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/17 16:04:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_utils.h"
#include "ast.h"

// static char	*get_program_name(char *set);

void	mini_safe_free(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

static void	kill_all(t_node *node)
{
	if (!node)
		return ;
	kill_all(node->lhs);
	kill_all(node->rhs);
	if (node->kind == ND_CMD)
		kill(node->cmd->pid, SIGINT);
}

void	t_mini_free(t_mini *mini)
{
	size_t	i;

	i = 0;
	while (i < mini->envp_len)
	{
		if (mini->envp[i])
			free(mini->envp[i]);
		i++;
	}
	free(mini->envp);
	if (mini->is_sys_err)
		kill_all(mini->node);
	free_node(&mini->node);
	mini_safe_free((void **)&mini->line);
	rl_clear_history();
}

void	update_pwd(t_mini *mini)
{
	size_t	pwd_i;
	char	*cwd_path;

	pwd_i = search_envp_i(mini, ENV_PWD, ENV_PWD_LEN);
	if (!mini->envp[pwd_i])
		return ;
	cwd_path = mini_getcwd();
	if (!cwd_path)
		return ;
	if (set_mini_envp(ENV_PWD, cwd_path, &mini->envp[pwd_i]))
	{
		free(cwd_path);
		systemcall_minishell_exit(mini, "malloc");
		return ;
	}
	free(cwd_path);
	return ;
}

int	set_mini_envp(char *var, char *val, char **envp_i)
{
	size_t	len;
	size_t	i;
	size_t	var_len;
	size_t	val_len;

	if (*envp_i)
		free(*envp_i);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	len = var_len + 1 + val_len;
	*envp_i = ft_calloc(len + 1, sizeof(char));
	if (!*envp_i)
		return (ERR);
	i = 0;
	ft_memmove(*envp_i, var, var_len);
	i += var_len;
	ft_memmove(*envp_i + i, "=", 1);
	i += 1;
	ft_memmove(*envp_i + i, val, val_len);
	return (SUCCESS);
}

// caution: the name should
// set only once throughout
// the program.
// set char *set NULL then
// you can get program_name
// set's len exceeds FILENAME_MAX
// then return NULL
// char	*access_program_name(char *set)
// {
// 	static char	name[FILENAME_MAX];
// 	char		*actual_name;

// 	if (!set)
// 		return (name);
// 	actual_name = get_program_name(set);
// 	if (FILENAME_MAX < ft_strlen(actual_name))
// 		return (ft_putstr_fd(actual_name, STDERR_FILENO), 
// 		ft_putendl_fd(": File name too long", STDERR_FILENO), NULL);
// 	ft_strlcpy(name, actual_name, FILENAME_MAX);
// 	return (name);
// }

// static char	*get_program_name(char *set)
// {
// 	char	*program_name;
// 	char	*tmp;

// 	program_name = ft_strchr(set, '/');
// 	if (!program_name)
// 		program_name = set;
// 	else
// 	{
// 		tmp = program_name;
// 		while (1)
// 		{
// 			program_name = ft_strchr(tmp + 1, '/');
// 			if (!program_name)
// 				break ;
// 			tmp = program_name;
// 		}
// 		program_name = tmp + 1;
// 	}
// 	return (program_name);
// }

// void	free_split(char **splited)
// {
// 	size_t	i;

// 	i = 0;
// 	while (splited[i])
// 		mini_safe_free((void **)&splited[i++]);
// 	mini_safe_free((void **)&splited);
// }
