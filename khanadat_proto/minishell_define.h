#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H
# include "ast_define.h"

# define BUILTIN_NUM 7
# define NO_NEW_LINE 1
# define DEFAULT_SIG_NUM 128
# define GOT_SIGNAL 130
# define PROMPT_CONTINUE 5
# define STATUS_SIZE 6

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

// int	received_sig;

typedef struct s_mini
{
	char	**envp;
	size_t	envp_size; // array's size
	size_t	envp_len; // actual stored size of envp
	char	*prompt;
	char	*line;
	char	*heredoc_name; // no need free
	t_node	*node;
	char	status[STATUS_SIZE];
}	t_mini;

#endif