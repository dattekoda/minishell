#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H
# include "tokenizer_define.h"
# include "ast_define.h"

typedef struct s_mini
{
	char	**envp;
	size_t	envp_size;
	size_t	envp_count;
	char	*prompt;
	t_node	*node;
}	t_mini;

#endif