#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H
# include "ast_define.h"

# define BUILTIN_NUM 7
# define NO_NEW_LINE 1
# define DEFAULT_SIG_NUM 128
# define GOT_SIGNAL 130
# define PROMPT_CONTINUE 5
# define STATUS_SIZE 6
# define PID_BUILTIN -2

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# ifndef MINISHELL_STR
#  define MINISHELL_STR "minishell"
# endif
// int	received_sig;

# ifndef ENV_PWD
#  define ENV_PWD "PWD"
# endif

# ifndef ENV_PWD_LEN
#  define ENV_PWD_LEN 3
# endif

# define INT_LEN_MAX 12

# define SHLVL_LEN 5

typedef struct s_mini
{
	bool	is_sys_err;
	bool	is_pipe;
	bool	signaled;
	char	**envp;
	size_t	envp_size; // array's size
	size_t	envp_len; // actual stored size of envp
	char	*prompt;
	char	*line;
	char	*mini_pwd;
	t_node	*node;
	char	status[STATUS_SIZE];
}	t_mini;

#endif