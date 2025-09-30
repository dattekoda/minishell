/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dollar_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:55:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 13:57:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_DOLLAR_UTILS_H
# define SEARCH_DOLLAR_UTILS_H

# include "minishell_define.h"
# include "expand_define.h"

t_dollar	*add_dollar(t_dollar *cur, t_mini *mini, \
	char **word, t_WordKind kind);
t_dollar	*add_single(t_dollar *cur, char **word);
t_dollar	*add_double(t_dollar *cur, char **word);
t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp);
t_dollar	*add_outside(t_dollar *cur, char **word);

#endif