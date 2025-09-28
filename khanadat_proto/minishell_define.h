#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H
# include "ast_define.h"

# define BUILTIN_NUM 7
# define NO_NEW_LINE 1
# define GOT_SIGNAL 130
# define PROMPT_CONTINUE 5

typedef struct s_mini
{
	char	**envp;
	size_t	envp_size; // array's size
	size_t	envp_len; // actual stored size of envp
	char	*prompt;
	char	*line;
	t_node	*node;
}	t_mini;

#endif