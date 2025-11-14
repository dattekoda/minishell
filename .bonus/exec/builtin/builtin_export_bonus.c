/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:52:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 21:09:39 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "builtin_utils_bonus.h"
#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "minishell_err_bonus.h"

#include "libft.h"

#define CONTINUE_STATUS 1
#define PLUS_EXPORT 2
#define NORMAL_EXPORT 3
#define NO_EQUALL 4

static int	export_no_eq(t_mini *mini, char *arg, size_t var_len);
static int	export_plus(t_mini *mini, char *arg, size_t	var_len);
static int	export_arg(t_mini *mini, char *arg, size_t var_len);
static int	check_valid_arg_export(char *argv_i, size_t *var_len);

void	exec_export(t_mini *mini, char **argv)
{
	size_t	i;
	size_t	var_len;
	int		status;

	if (!argv[1])
		exec_env(mini, argv, true);
	i = 0;
	while (argv[++i])
	{
		status = check_valid_arg_export(argv[i], &var_len);
		if (status == FAILURE)
		{
			store_status(FAILURE, mini);
			err_export(argv[i]);
			return ;
		}
		if (status == NO_EQUALL && export_no_eq(mini, argv[i], var_len))
			systemcall_minishell_exit(mini, "malloc");
		if (status == PLUS_EXPORT && export_plus(mini, argv[i], var_len))
			systemcall_minishell_exit(mini, "malloc");
		if (status == NORMAL_EXPORT && export_arg(mini, argv[i], var_len))
			systemcall_minishell_exit(mini, "malloc");
	}
	store_status(SUCCESS, mini);
}

static int	export_no_eq(t_mini *mini, char *arg, size_t var_len)
{
	size_t	i;

	i = search_envp_i(mini, arg, var_len);
	if (mini->envp[i])
		return (SUCCESS);
	else if (!mini->envp[i] && add_mini_len(mini))
		return (ERR);
	mini->envp[i] = ft_strdup(arg);
	if (!mini->envp[i])
		return (ERR);
	return (SUCCESS);
}

static int	export_plus(t_mini *mini, char *arg, size_t	var_len)
{
	size_t	i;
	char	*tmp;

	i = search_envp_i(mini, arg, var_len);
	if (mini->envp[i])
	{
		if (ft_strchr(mini->envp[i], '='))
			tmp = ft_strjoin(mini->envp[i], ft_strchr(arg, '=') + 1);
		else
			tmp = ft_strjoin(mini->envp[i], ft_strchr(arg, '+') + 1);
		free(mini->envp[i]);
		mini->envp[i] = tmp;
	}
	else
	{
		tmp = ft_strchr(arg, '+');
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp));
		if (add_mini_len(mini))
			return (ERR);
		mini->envp[i] = ft_strdup(arg);
	}
	if (!mini->envp[i])
		return (ERR);
	return (SUCCESS);
}

static int	export_arg(t_mini *mini, char *arg, size_t var_len)
{
	size_t	i;

	i = search_envp_i(mini, arg, var_len);
	if (mini->envp[i])
		free(mini->envp[i]);
	else if (!mini->envp[i] && add_mini_len(mini))
		return (ERR);
	mini->envp[i] = ft_strdup(arg);
	if (!mini->envp[i])
		return (ERR);
	return (SUCCESS);
}

// if continue then return 1
// if += then return 2
// if = then return 3
// if invalid argv_i then return -1
static int	check_valid_arg_export(char *argv_i, size_t *var_len)
{
	char	*eq_ptr;
	char	*plus_ptr;
	size_t	j;

	j = 0;
	while (ft_isalpha(argv_i[j]) || argv_i[j] == '_')
		j++;
	if (argv_i[j] != '=' && argv_i[j] != '+' && argv_i[j])
		return (FAILURE);
	eq_ptr = ft_strchr(argv_i, '=');
	if (!eq_ptr)
	{
		*var_len = ft_strlen(argv_i);
		return (NO_EQUALL);
	}
	*var_len = (size_t)(eq_ptr - argv_i);
	plus_ptr = ft_strchr(argv_i, '+');
	if (plus_ptr && plus_ptr + 1 == eq_ptr)
		*var_len = (size_t)(plus_ptr - argv_i);
	if (plus_ptr && plus_ptr + 1 == eq_ptr)
		return (PLUS_EXPORT);
	return (NORMAL_EXPORT);
}
