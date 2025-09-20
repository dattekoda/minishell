#ifndef AST_H
# define AST_H

# include "ast_define.h"
# include "tokenizer_define.h"

void	free_node(t_node *node);
int		get_node(t_node **node, t_token *token);

#endif