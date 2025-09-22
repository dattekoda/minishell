/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 14:03:38 by khanadat         ###   ########.fr       */
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
	ND_PIPE
}	t_NodeKind;

typedef enum s_RedKind
{
	RD_IN,
	RD_OUT,
	RD_HEREDOC,
	RD_APPEND
}	t_RedKind;

typedef struct s_red
{
	char			*file;
	t_RedKind		kind;
	struct s_red	*next;
}	t_red;

// abstruct syntax tree
typedef struct s_node
{
	t_red			*red;
	size_t			argv_size;
	size_t			word_num;
	char			**argv;
	struct s_node	*lhs;
	struct s_node	*rhs;
	t_NodeKind		kind;
}	t_node;

#endif