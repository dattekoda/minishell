/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:59:02 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/11 19:52:59 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_DEFINE_H
# define TOKENIZER_DEFINE_H

# include <stddef.h>

# define SPECIAL_CHAR "&|<>()"

typedef enum s_TokenKind
{
	TK_WORD,
	TK_OPERATOR,
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_REDIN,
	TK_HEREDOC,
	TK_APPEND,
	TK_REDOUT,
	TK_FIRST_PAR,
	TK_SEC_PAR,
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