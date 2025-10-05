/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:16:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 23:48:19 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_UTILS_H
# define BUILTIN_UTILS_H

# include "minishell_define.h"

void	exec_cd(t_mini *mini, char **argv);
void	exec_echo(t_mini *mini, char **argv);
void	exec_env(t_mini *mini, char **argv);
void	exec_exit(t_mini *mini, char **argv);
void	exec_export(t_mini *mini, char **argv);
void	exec_pwd(t_mini *mini, char **argv);
void	exec_unset(t_mini *mini, char **argv);

#endif