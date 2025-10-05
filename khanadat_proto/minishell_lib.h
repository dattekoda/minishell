#ifndef MINISHELL_LIB_H
# define MINISHELL_LIB_H

# include "minishell_define.h"

// lib0
int		safe_join(char **joined, char *buffer);
void	minishell_exit(t_mini *mini);
void	failure_minishell_exit(t_mini *mini, void (*func)(char *), char *file, int status);
void	systemcall_minishell_exit(t_mini *mini, char *func);
void	child_minishell_exit(t_mini *mini, void (*func)(char *), \
	char **argv, int status);

// lib1
void	mini_safe_free(void **ptr);
void	t_mini_free(t_mini *mini);
char	*access_program_name(char *set);
void	free_split(char **splited);

// lib2
char	*normal_getenv(char *var, t_mini *mini);
char	*mini_getenv(char **var, t_mini *mini);
void	store_status(unsigned char status, t_mini *mini);
bool	mini_is_dir(char *file);

// lib3
void	catch_signal(int status, t_mini *mini);
int		set_handler(int sig, void handler(int));
void	quit_cmd(int sig);
void	restart_prompt(int sig);

// lib4
void	normal_minishell_exit(t_mini *mini, void (*func)(void *), \
	void *ptr, int status);
size_t	search_envp_i(t_mini *mini, char *arg, size_t var_len);
char	*mini_getcwd(void);
int		add_mini_len(t_mini *mini);

#endif