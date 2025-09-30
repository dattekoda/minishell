/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:14:47 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 16:14:48 by khanadat         ###   ########.fr       */
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

#endif