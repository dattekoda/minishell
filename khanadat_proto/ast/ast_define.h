#ifndef AST_DEFINE_H
# define AST_DEFINE_H

typedef enum {
	ND_CMD,
	ND_AND,
	ND_OR,
	ND_PIPE,
}	NodeKind;

// abstruct syntax tree
typedef struct s_node
{
	char			**argv;
	struct s_node	*lhs;
	struct s_node	*rhs;
	NodeKind		kind;
}	t_node;

#endif