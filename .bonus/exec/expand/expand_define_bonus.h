/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_define_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:26:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_DEFINE_BONUS_H
# define EXPAND_DEFINE_BONUS_H

# include <stddef.h>
# include <stdbool.h>

typedef enum s_DollarKind
{
	WD_WORD,
	WD_SPACE,
	WD_HEAD
}	t_DollarKind;

typedef struct s_dollar
{
	bool			is_quoted;
	char			*orig;
	char			*value;
	size_t			value_len;
	t_DollarKind	dkind;
	struct s_dollar	*next;
}	t_dollar;

#endif