/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:45:58 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/14 22:29:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include "ast_define.h"
#include <stdio.h>

# define ERR -1
# define NO_ERR 0
# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERR 2

# define IS_DIR_ERR 126
# define PERMISSION_ERR 126
# define NOT_FOUND_ERR 127
# define SYSTEMCALL_EXITSTATUS 255

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

# define MINISHELL_STR "minishell"
# define ENV_PWD "PWD"
# define ENV_PWD_LEN 3
# define ENV_OLDPWD "OLDPWD"
# define ENV_OLDPWD_LEN 6
# define INT_LEN_MAX 12
# define SHLVL_LEN 5

// @envp_size: array's size
// @envp_len: actual stored size of envp
typedef struct s_mini
{
	bool	is_sys_err;
	bool	is_pipe;
	bool	is_inside;
	bool	signaled;
	char	**envp;
	size_t	envp_size;
	size_t	envp_len;
	char	*prompt;
	char	*line;
	t_node	*node;
	char	status[STATUS_SIZE];
}	t_mini;

#endif