/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:58:13 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 13:01:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell_define.h"

int		expand_node(t_node *node, t_mini *mini);
void	set_wild_word(t_mini *mini, t_word **word);

#endif