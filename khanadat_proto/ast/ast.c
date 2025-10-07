/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 08:14:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "status.h"
#include "minishell_define.h"
#include "minishell_err.h"
#include "tokenizer.h"
#include "ast_define.h"
#include "ast_utils.h"
#include "ast.h"

static void	free_cmd(t_cmd *cmd);

void	free_node(t_node **node)
{
	if (!*node)
		return ;
	if ((*node)->kind != ND_CMD)
	{
		free_node(&((*node)->lhs));
		free_node(&((*node)->rhs));
	}
	if ((*node)->kind == ND_CMD)
	{
		free_word((*node)->word);
		free_red((*node)->red);
		free_cmd((*node)->cmd);
	}
	free(*node);
	*node = NULL;
}

static void	free_cmd(t_cmd *cmd)
{
	free(cmd->argv);
	if (cmd->cfd[0] != STDIN_FILENO)
		close(cmd->cfd[0]);
	if (cmd->cfd[1] != STDOUT_FILENO)
		close(cmd->cfd[1]);
	if (!access(cmd->heredoc_name, F_OK))
		unlink(cmd->heredoc_name);
	free(cmd->heredoc_name);
	free(cmd);
}

int	validate_token(t_token *token)
{
	if (is_pipe_or_and(token))
		return (err_tokenizer(token), SYNTAX_ERR);
	while (token->kind != TK_EOF)
	{
		if (is_redirect(token))
		{
			if ((token->next)->kind != TK_WORD)
				return (err_tokenizer(token->next), SYNTAX_ERR);
			token = token->next;
		}
		else if (is_pipe_or_and(token))
		{
			if ((token->next)->kind == TK_EOF \
			|| is_pipe_or_and(token->next))
				return (err_tokenizer(token->next), SYNTAX_ERR);
			token = token->next;
		}
		token = token->next;
	}
	return (SUCCESS);
}

// syntax err return 2
// system call err return -1
int	get_node(t_node **node, t_token *token)
{
	t_node	*cur;
	t_node	*before;

	if (token->kind == TK_EOF || validate_token(token))
		return (SYNTAX_ERR);
	cur = new_pipe_node(&token);
	while (cur)
	{
		before = cur;
		if (consume_node(&token, TK_OPERATOR, ND_OR))
			cur = new_node(ND_OR, cur, new_pipe_node(&token));
		else if (consume_node(&token, TK_OPERATOR, ND_AND))
			cur = new_node(ND_AND, cur, new_pipe_node(&token));
		else
			break ;
	}
	if (!cur)
		return (free_node(&before), ERR);
	*node = cur;
	return (SUCCESS);
}
