/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iokuno <iokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:26:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 22:54:04 by iokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_DEFINE_H
# define EXPAND_DEFINE_H

# include <stdbool.h>
# include <stddef.h>

typedef enum s_DollarKind
{
	WD_WORD,
	WD_SPACE,
	WD_HEAD
}					t_DollarKind;

typedef struct s_dollar
{
	bool			is_quoted;
	char			*value;
	size_t			value_len;
	t_DollarKind	dkind;
	struct s_dollar	*next;
}					t_dollar;

#endif