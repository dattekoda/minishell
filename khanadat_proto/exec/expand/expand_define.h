/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:26:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 14:13:04 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_DEFINE_H
# define EXPAND_DEFINE_H

# include <stddef.h>

// WD_DDOLLAR: inside double dollar
typedef enum s_WordKind
{
	WD_DOLLAR,
	WD_SINGLE,
	WD_DOUBLE,
	WD_DDOLLAR,
	WD_OUTSIDE,
	WD_EOF
}	t_WordKind;

typedef struct s_dollar
{
	char			*value;
	size_t			value_len;
	t_WordKind		wkind;
	struct s_dollar	*next;
}	t_dollar;

#endif