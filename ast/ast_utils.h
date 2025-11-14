/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/14 22:08:09 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_UTILS_H
# define AST_UTILS_H

# include <stdbool.h>
# include "ast_define.h"
# include "tokenizer.h"

// ast_utils.c
t_node		*new_node(t_NodeKind kind, t_node *lhs, t_node *rhs);
bool		consume_redirect(t_token **token, \
	t_TokenKind tkind, t_RedKind rkind);
bool		consume_node(t_token **token, t_TokenKind tkind, t_NodeKind nkind);
t_node		*new_pipe_node(t_token **token);

// ast_utils_cmd.c
t_node		*new_cmd_node(t_token **token);

// ast_utils_red.c
int			set_redirection(t_token *token, t_node *new);
t_RedKind	check_redkind(t_token *token);

// ast_is.c
bool		is_pipe_or_and(t_token *token);
bool		is_or_and(t_token *token);
bool		is_pipe(t_token *token);
bool		is_and(t_token *token);
bool		is_or(t_token *token);

bool		is_redirect(t_token *token);
bool		is_red_in(t_token *token);
bool		is_red_out(t_token *token);
bool		is_red_append(t_token *token);
bool		is_red_heredoc(t_token *token);

bool		is_par_first(t_token *token);
bool		is_par_sec(t_token *token);

// ast_utils_new_node.c
t_node		*new_and_or_node(t_token **token);
t_node		*new_inside_node(t_token **token);

// ast_utils_valid.c
int			validate_token(t_token *token);

#endif