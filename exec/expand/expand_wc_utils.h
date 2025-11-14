/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:30:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 14:33:27 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_WC_UTILS_H
# define EXPAND_WC_UTILS_H

# include <stdbool.h>
# include <stddef.h>

bool	need_expand_wild(bool *wild_checker, char *expanded, size_t exp_len);
bool	is_wildcard(char *pattern, char *d_name);

#endif