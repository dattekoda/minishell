/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 14:04:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_UTILS_H
# define AST_UTILS_H

# include <stdbool.h>
# include "ast_define.h"
# include "tokenizer.h"

void	free_red(t_red *head);
t_node	*new_node(t_NodeKind kind, t_node *lhs, t_node *rhs);
bool	consume_redirect(t_token **token, t_TokenKind tkind, t_RedKind rkind);
bool	consume_node(t_token **token, t_TokenKind tkind, t_NodeKind nkind);
t_node	*new_pipe_node(t_token **token);

#endif