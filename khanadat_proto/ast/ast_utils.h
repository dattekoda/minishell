#ifndef AST_UTILS_H
# define AST_UTILS_H

# include <stdbool.h>
# include "ast_define.h"
# include "tokenizer.h"

void	free_red(t_red *head);
t_node	*new_node(t_NodeKind kind, t_node *lhs, t_node *rhs);
bool	consume(t_token **token, t_TokenKind tkind, t_NodeKind nkind);
t_node	*pipe_node(t_token **token);

#endif