/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 14:00:53 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_DEFINE_H
# define AST_DEFINE_H

# include <stdbool.h>
# include <stddef.h>

typedef enum s_NodeKind
{
	ND_CMD,
	ND_AND,
	ND_OR,
	ND_PIPE,
	ND_NOT
}	t_NodeKind;

typedef enum s_RedKind
{
	RD_IN,
	RD_OUT,
	RD_HEREDOC,
	RD_APPEND,
	RD_NOT
}	t_RedKind;

typedef struct s_red
{
	char			*file;
	t_RedKind		kind;
	struct s_red	*next;
}	t_red;

typedef struct s_word
{
	char			*word;
	size_t			word_len;
	struct s_word	*next;
}	t_word;

// abstruct syntax tree
typedef struct s_node
{
	t_red			*red;
	t_word			*word;
	struct s_node	*lhs;
	struct s_node	*rhs;
	t_NodeKind		kind;
}	t_node;

#endif