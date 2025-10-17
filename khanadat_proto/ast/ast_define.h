/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/16 21:25:26 by khanadat         ###   ########.fr       */
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
	ND_PAR_FIRST,
	ND_PAR_SEC,
	ND_INSIDE,
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
	bool			is_quoted;
	char			*file;
	size_t			file_len;
	char			*expanded;
	size_t			exp_len;
	t_RedKind		kind;
	struct s_red	*next;
}	t_red;

typedef struct s_word
{
	char			*word;
	size_t			word_len;
	char			*expanded;
	size_t			exp_len;
	struct s_word	*next;
}	t_word;

typedef struct s_cmd
{
	pid_t	pid;
	int		pfd[2];
	int		saved[2];
	int		rfd[2];
	char	**argv;
	char	*heredoc_name;
}	t_cmd;

// abstruct syntax tree
typedef struct s_node
{
	bool			expand_err;
	t_red			*red;
	t_word			*word;
	t_cmd			*cmd;
	struct s_node	*lhs;
	struct s_node	*rhs;
	t_NodeKind		kind;
}	t_node;

#endif