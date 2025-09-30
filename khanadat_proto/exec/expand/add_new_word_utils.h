/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_word_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:05:31 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 14:08:50 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_NEW_WORD_UTILS_H
# define ADD_NEW_WORD_UTILS_H

# include "minishell_define.h"
# include "expand_define.h"

bool	need_split(t_dollar **dol, size_t *len);
size_t	count_word_len(t_dollar **dol);
void	set_word_word(t_word *new_word, t_dollar *dol_tail);

#endif