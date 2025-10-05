/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:14:47 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/05 17:22:48 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERR_H
# define MINISHELL_ERR_H

# include "tokenizer.h"

// minishll_err.c
void	err_cmd_not_found(char *file);
void	err_tokenizer(t_token *token);
void	err_invalid_arg(char *program_name);
void	err_system_call(char *func);
void	put_syntax_err(char type);

// minishell_err1.c
void	err_permission(char *file);
void	err_is_dir(char *file);
void	err_heredoc(char *file);
void	err_no_file(char *file);
void	err_ambiguous(char *file);

// minishell_err2.c
void	err_cd(char *file);
void	err_no_home(char *file);
void	err_too_many(char *file);
void	err_not_dir(char *file);
void	err_cd_permission(char *file);

// minishell_err3.c
void	err_msg_env(char *file);
void	err_export(char *file);
void	err_exit_numeric(char *file);

#endif