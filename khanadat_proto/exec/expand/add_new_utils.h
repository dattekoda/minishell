/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dollar_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:05:31 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 14:08:50 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_NEW_UTILS_H
# define ADD_NEW_UTILS_H

# include "minishell_define.h"
# include "expand_define.h"

void	set_new_str(char *str, t_dollar *dol_tail);
size_t	count_word_len(t_dollar **dol);

#endif