/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_err0_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:14:49 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_bonus.h"
#include "minishell_utils_bonus.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	err_cmd_not_found(char *file)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	err_tokenizer(t_token *token)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": syntax error" \
		" near unexpected token `", STDERR_FILENO);
	if (token->kind == TK_EOF)
		ft_putstr_fd("new_line", STDERR_FILENO);
	else
		write(STDERR_FILENO, token->str, token->str_len);
	ft_putendl_fd("\'", STDERR_FILENO);
}

// used only at first
void	err_invalid_arg(char *program_name)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": Error: ", STDERR_FILENO);
	ft_putstr_fd(program_name, STDERR_FILENO);
	ft_putendl_fd(": invalid number of arguments", STDERR_FILENO);
}

// set function's name
// and put msg to err_fileno like
// Error: malloc failed.\n
void	err_system_call(char *func)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": Error: ", STDERR_FILENO);
	perror(func);
}

void	put_syntax_err(char type)
{
	ft_putstr_fd(MINISHELL_STR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("syntax error: ", STDERR_FILENO);
	if (type == '&')
		ft_putendl_fd("you cannot use '&'" \
			", job control function", STDERR_FILENO);
	else if (type == '\'')
		ft_putendl_fd("you need enclose with \'", STDERR_FILENO);
	else if (type == '\"')
		ft_putendl_fd("you need enclose with \"", STDERR_FILENO);
	else if (type == '(' || type == ')')
	{
		ft_putstr_fd("near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(type, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
}
