/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:52:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 23:34:20 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "builtin_utils.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "status.h"
#include "libft.h"

#define CONTINUE_STATUS 1
#define PLUS_EXPORT 2
#define NORMAL_EXPORT 3

static int	export_plus(t_mini *mini, char *arg, size_t	var_len);
static int	export_arg(t_mini *mini, char *arg, size_t var_len);
static int	check_valid_arg_export(t_mini *mini, char *argv_i, size_t *var_len);

void	exec_export(t_mini *mini, char **argv)
{
	size_t	i;
	size_t	var_len;
	int		status;

	if (!argv[1])
		exec_env(mini, argv);
	i = 0;
	while (argv[++i])
	{
		status = check_valid_arg_export(mini, argv[i], &var_len);
		if (status == CONTINUE_STATUS)
			continue ;
		if (status == ERR)
			return ;
		if (status == PLUS_EXPORT \
			&& export_plus(mini, argv[i], var_len))
			normal_minishell_exit(mini, &free, \
				argv, SYSTEMCALL_EXITSTATUS);
		if (status == NORMAL_EXPORT \
			&& export_arg(mini, argv[i], var_len))
			normal_minishell_exit(mini, &free, \
				argv, SYSTEMCALL_EXITSTATUS);
	}
	store_status(SUCCESS, mini);
}

static int	export_plus(t_mini *mini, char *arg, size_t	var_len)
{
	size_t	i;
	char	*tmp;
	char	*plus_ptr;

	plus_ptr = ft_strchr(arg, '+');
	ft_memmove(plus_ptr, plus_ptr + 1, ft_strlen(plus_ptr));
	i = search_envp_i(mini, arg, var_len);
	if (mini->envp[i])
	{
		tmp = ft_strjoin(mini->envp[i], ft_strchr(arg, '=') + 1);
		free(mini->envp[i]);
		mini->envp[i] = tmp;
	}
	else
	{
		if (add_mini_len(mini))
			return (err_system_call("malloc"), ERR);
		mini->envp[i] = ft_strdup(arg);
	}
	if (!mini->envp[i])
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}

static int	export_arg(t_mini *mini, char *arg, size_t var_len)
{
	size_t	i;

	i = search_envp_i(mini, arg, var_len);
	if (mini->envp[i])
		free(mini->envp[i]);
	else if (!mini->envp[i] && add_mini_len(mini))
		return (err_system_call("malloc"), ERR);
	mini->envp[i] = ft_strdup(arg);
	if (!mini->envp[i])
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}

// if continue then return 1
// if += then return 2
// if = then return 3
// if invalid argv_i then return -1
static int	check_valid_arg_export(t_mini *mini, char *argv_i, size_t *var_len)
{
	char	*eq_ptr;
	char	*plus_ptr;

	eq_ptr = ft_strchr(argv_i, '=');
	if (!eq_ptr)
		return (CONTINUE_STATUS);
	*var_len = (size_t)(eq_ptr - argv_i);
	plus_ptr = ft_strchr(argv_i, '+');
	if (plus_ptr && plus_ptr + 1 == eq_ptr)
		*var_len = (size_t)(plus_ptr - argv_i);
	if (!*var_len || (*var_len == 1 && *argv_i == '$')
		|| (plus_ptr && plus_ptr + 1 < eq_ptr))
	{
		err_export(argv_i);
		store_status(FAILURE, mini);
		return (ERR);
	}
	if (plus_ptr && plus_ptr + 1 == eq_ptr)
		return (PLUS_EXPORT);
	return (NORMAL_EXPORT);
}
