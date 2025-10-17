/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:27:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/16 22:55:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "minishell_define.h"
# include "expand_define.h"

// expand_utils.c
void	free_dollar(t_dollar *head);
int		get_dollar(char *str, t_mini *mini, t_dollar **dol);

// expand_utils_add.c
t_word	*add_new_word(t_word *cur, t_dollar **dol);
t_red	*add_new_red(t_red *cur, t_dollar **dol, t_red *before);

#endif