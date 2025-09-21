/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/21 09:58:45 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_DEFINE_H
# define AST_DEFINE_H

# include <stdbool.h>

typedef enum s_NodeKind
{
	ND_CMD,
	ND_AND,
	ND_OR,
	ND_RED_IN,
	ND_RED_OUT,
	ND_HEREDOC,
	ND_APPEND,
	ND_PIPE
}	t_NodeKind;

typedef struct s_red
{
	char			*file;
	t_NodeKind		kind;
	struct s_red	*next;
}	t_red;

// abstruct syntax tree
typedef struct s_node
{
	t_red			*red;
	char			**argv;
	struct s_node	*lhs;
	struct s_node	*rhs;
	t_NodeKind		kind;
}	t_node;

#endif