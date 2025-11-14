/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:45:46 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 18:04:56 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_utils.h"
#include "ast_define.h"
#include "minishell_define.h"
#include "tokenizer_define.h"
#include "libft.h"

#ifndef CMD_END
# define CMD_END 3
#endif

static int		set_word(t_token **token, t_node *new);
static t_word	*add_new_word(t_word *cur, t_token *token);
static int		set_cmd(t_node *new);

void	free_word(t_word *head)
{
	t_word	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->expanded);
		free(head->wild_checker);
		free(head);
		head = tmp;
	}
}

t_node	*new_cmd_node(t_token **token)
{
	t_node	*new;

	if (is_par_first(*token))
		return (new_inside_node(token));
	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	if (set_redirection(*token, new))
		return (free(new), NULL);
	if (set_word(token, new))
		return (free_red(new->red), free(new), NULL);
	if (set_cmd(new))
		return (free_word(new->word), free_red(new->red), \
		free(new), NULL);
	new->kind = ND_CMD;
	return (new);
}

static int	set_word(t_token **token, t_node *new)
{
	t_word	head;
	t_word	*cur;

	ft_bzero(&head, sizeof(t_word));
	cur = &head;
	while ((*token)->kind != TK_EOF)
	{
		if ((*token)->kind == TK_OPERATOR \
			&& check_redkind(*token) == RD_NOT)
			break ;
		if ((*token)->kind == TK_OPERATOR)
		{
			(*token) = (*token)->next->next;
			continue ;
		}
		cur = add_new_word(cur, (*token));
		if (!cur)
			return (free_word(head.next), ERR);
		(*token) = (*token)->next ;
	}
	new->word = head.next;
	return (SUCCESS);
}

static t_word	*add_new_word(t_word *cur, t_token *token)
{
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return (free(new), NULL);
	new->word = token->str;
	new->word_len = token->str_len;
	cur->next = new;
	return (new);
}

static int	set_cmd(t_node *new)
{
	new->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new->cmd)
		return (ERR);
	new->cmd->pfd[0] = FD_DFL;
	new->cmd->pfd[1] = FD_DFL;
	new->cmd->rfd[0] = FD_DFL;
	new->cmd->rfd[1] = FD_DFL;
	return (SUCCESS);
}
