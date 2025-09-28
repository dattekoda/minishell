#ifndef MINISHELL_ERR_H
# define MINISHELL_ERR_H

# include "tokenizer.h"
// minishll_err.c

// used only at first
void	err_tokenizer(t_token *token);
void	err_invalid_arg(char *program_name);
void	err_system_call(char *func);
void	put_syntax_err(char type);

#endif