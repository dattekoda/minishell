/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/01 12:01:57 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_UTILS_H
# define AST_UTILS_H

# include <stdbool.h>
# include "ast_define.h"
# include "tokenizer.h"

// ast_utils.c
t_node	*new_node(t_NodeKind kind, t_node *lhs, t_node *rhs);
bool	consume_redirect(t_token **token, t_TokenKind tkind, t_RedKind rkind);
bool	consume_node(t_token **token, t_TokenKind tkind, t_NodeKind nkind);
t_node	*new_pipe_node(t_token **token);

// ast_utils_node.c
t_node	*new_cmd_node(t_token **token);

// ast_utils_red.c
int			set_redirection(t_token *token, t_node *new);
t_RedKind	check_redkind(t_token *token);

#endif