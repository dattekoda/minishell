/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:37 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_define_bonus.h"
#include "minishell_err_bonus.h"
#include "minishell_utils_bonus.h"
#include "tokenizer_bonus.h"
#include "ast_define_bonus.h"
#include "ast_utils_bonus.h"
#include "ast_bonus.h"
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

static void	free_cmd(t_cmd *cmd);
void		put_eof_cmd_node(t_node *node);

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
	if (cmd->pfd[0] != FD_DFL)
		close(cmd->pfd[0]);
	if (cmd->pfd[1] != FD_DFL)
		close(cmd->pfd[1]);
	if (cmd->rfd[0] != FD_DFL)
		close(cmd->rfd[0]);
	if (cmd->rfd[1] != FD_DFL)
		close(cmd->rfd[1]);
	safe_delete_heredoc_file(&cmd->heredoc_name);
	free(cmd);
}

// syntax err return 2
// system call err return -1
int	get_node(t_node **node, t_token *token)
{
	t_node	*cur;

	if (token->kind == TK_EOF)
		return (PROMPT_CONTINUE);
	if (validate_token(token))
		return (SYNTAX_ERR);
	cur = new_and_or_node(&token);
	if (!cur)
		return (ERR);
	put_eof_cmd_node(cur);
	*node = cur;
	return (SUCCESS);
}

void	put_eof_cmd_node(t_node *node)
{
	t_word	*tmp_word;
	t_red	*tmp_red;

	if (!node)
		return ;
	if (node->kind == ND_CMD)
	{
		tmp_word = node->word;
		while (tmp_word)
		{
			tmp_word->word[tmp_word->word_len] = '\0';
			tmp_word = tmp_word->next;
		}
		tmp_red = node->red;
		while (tmp_red)
		{
			tmp_red->file[tmp_red->file_len] = '\0';
			tmp_red = tmp_red->next;
		}
	}
	put_eof_cmd_node(node->lhs);
	put_eof_cmd_node(node->rhs);
}
