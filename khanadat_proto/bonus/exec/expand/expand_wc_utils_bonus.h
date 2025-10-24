/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_utils_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:30:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_WC_UTILS_BONUS_H
# define EXPAND_WC_UTILS_BONUS_H

# include <stdbool.h>
# include <stddef.h>

bool	need_expand_wild(bool *wild_checker, char *expanded, size_t exp_len);
bool	is_wildcard(char *pattern, char *d_name);

#endif