/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:16:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_BONUS_H
# define BUILTIN_UTILS_BONUS_H

# include "minishell_define_bonus.h"

void	exec_cd(t_mini *mini, char **argv);
void	exec_echo(t_mini *mini, char **argv);
void	exec_env(t_mini *mini, char **argv, bool exp);
void	exec_exit(t_mini *mini, char **argv);
void	exec_export(t_mini *mini, char **argv);
void	exec_pwd(t_mini *mini);
void	exec_unset(t_mini *mini, char **argv);

#endif