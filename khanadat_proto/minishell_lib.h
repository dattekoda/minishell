#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

# include "minishell_define.h"

int		safe_join(char **joined, char *buffer);
void	free_minienvp(t_mini *mini);
void	safe_minishell_exit(t_mini *mini);
char	*mini_getenv(char *var, t_mini *mini);

#endif