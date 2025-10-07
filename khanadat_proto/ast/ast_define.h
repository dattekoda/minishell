/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 08:15:51 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_DEFINE_H
# define AST_DEFINE_H

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

# define FD_DFL -2

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

typedef struct s_cmd
{
	pid_t	pid;
	int		cfd[2];
	int		saved[2];
	int		rfd[2];
	char	**argv;
	char	*heredoc_name; // need free
}	t_cmd;

// abstruct syntax tree
typedef struct s_node
{
	t_red			*red;
	t_word			*word;
	t_cmd			*cmd;
	bool			ishead;
	struct s_node	*lhs;
	struct s_node	*rhs;
	t_NodeKind		kind;
}	t_node;

#endif