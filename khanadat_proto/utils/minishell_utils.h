/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:45:32 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 14:56:49 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# include "minishell_define.h"

// utils0
int		safe_join(char **joined, char *buffer);
void	minishell_exit(t_mini *mini);
void	failure_minishell_exit(t_mini *mini, \
	void (*func)(char *), char *file, int status);
void	systemcall_minishell_exit(t_mini *mini, char *func);

// utils1
void	mini_safe_free(void **ptr);
void	t_mini_free(t_mini *mini);
void	update_pwd(t_mini *mini);
int		set_mini_envp(char *var, char *val, char **envp_i);
// char	*access_program_name(char *set);
// void	free_split(char **splited);

// utils2
char	*normal_getenv(char *var, t_mini *mini);
char	*mini_getenv(char **var, t_mini *mini);
void	store_status(unsigned char status, t_mini *mini);
bool	mini_is_dir(char *file);

// utils3
void	catch_final_status(int status, t_mini *mini);
void	set_handler(t_mini *mini, int sig, void handler(int));
// void	quit_cmd(int sig);
// void	restart_prompt(int sig);

// utils4
void	normal_minishell_exit(t_mini *mini, void (*func)(void *), \
	void *ptr, int status);
size_t	search_envp_i(t_mini *mini, char *arg, size_t var_len);
char	*mini_getcwd(void);
int		add_mini_len(t_mini *mini);
void	safe_delete_heredoc_file(char **hd_name);

#endif