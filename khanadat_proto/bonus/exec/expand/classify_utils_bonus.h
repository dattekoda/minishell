/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_utils_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:16:09 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSIFY_UTILS_BONUS_H
# define CLASSIFY_UTILS_BONUS_H

# include "minishell_define_bonus.h"
# include "expand_define_bonus.h"

// classify_utils0.c
t_dollar	*classify_more_dollar(t_dollar **cur, t_mini *mini, char **tmp);
t_dollar	*add_single(t_dollar *cur, char **word);
t_dollar	*add_status(t_dollar *cur, t_mini *mini, \
	char **word, bool is_quoted);

// classify_utils1.c
t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp);
t_dollar	*add_outside(t_dollar *cur, char **word);

#endif