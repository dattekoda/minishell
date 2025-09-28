#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

# include "minishell_define.h"

// lib0
int		safe_join(char **joined, char *buffer);
void	noline_minishell_exit(t_mini *mini);
void	systemcall_minishell_exit(t_mini *mini, char *func);
char	*mini_getenv(char *var, t_mini *mini);

// lib1
void	safe_free(void **ptr);
void	free_program_name(void);
char	*access_program_name(char *set);
void	free_split(char **splited);

#endif