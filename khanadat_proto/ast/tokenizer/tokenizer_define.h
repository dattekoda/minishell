/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:59:02 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/21 09:59:03 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_DEFINE_H
# define TOKENIZER_DEFINE_H

# include <stddef.h>

# define SPECIAL_CHAR "&|<>"

typedef enum s_TokenKind
{
	TK_WORD,
	TK_OPERATOR,
	TK_EOF,
}	t_TokenKind;

typedef struct s_token
{
	char			*str;
	size_t			str_len;
	t_TokenKind		kind;
	struct s_token	*next;
}	t_token;

#endif