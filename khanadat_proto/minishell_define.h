#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H
# include "ast_define.h"

# define BUILTIN_NUM 7
# define NO_NEW_LINE 1
# define DEFAULT_SIG_NUM 128
# define GOT_SIGNAL 130
# define PROMPT_CONTINUE 5

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

int	received_sig;

typedef struct s_mini
{
	char	**envp;
	size_t	envp_size; // array's size
	size_t	envp_len; // actual stored size of envp
	char	*prompt;
	char	*line;
	t_node	*node;
	int		status;
}	t_mini;

#endif