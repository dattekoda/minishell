/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_set.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:42:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/10 08:56:46 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SET_H
# define MINISHELL_SET_H

# include "minishell_define.h"

int	set_minishell(t_mini *mini, char *envp[]);
int	set_node(t_mini *mini);

#endif