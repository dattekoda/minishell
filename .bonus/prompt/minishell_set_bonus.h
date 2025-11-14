/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:42:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 21:00:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SET_BONUS_H
# define MINISHELL_SET_BONUS_H

# include "minishell_define_bonus.h"

int	set_minishell(t_mini *mini, char *envp[]);
int	set_node(t_mini *mini);

#endif