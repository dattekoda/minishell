/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:46 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 14:06:59 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_define.h"
#include "tokenizer_define.h"
#include "status.h"
#include "minishell_err.h"
#include "ast_utils.h"
#include "libft.h"

#ifndef CMD_END
# define CMD_END 3
#endif

static int	set_node_argv(t_token **token, t_node *new);
static void	count_word_num(t_token *token, size_t *word_num);
static int	add_new_red(t_token *token, t_red **cur);
static int	set_redirection(t_token *token, t_node *new);

// malloc 2 times as many as number of words
// in order to ensure sufficient margin after
// variable expansion
t_node	*new_cmd_node(t_token **token)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	if (set_redirection(*token, new))
		return ((new->kind = ND_AND), NULL);
	count_word_num(*token, &new->word_num);
	new->argv_size = new->word_num * 2;
	new->argv = ft_calloc(new->argv_size + 1, sizeof(char *));
	if (!new->argv || set_node_argv(token, new))
		return (free_red(new->red), (new->kind = ND_AND), NULL);
	new->kind = ND_CMD;
	return (new);
}

static void	count_word_num(t_token *token, size_t *word_num)
{
	*word_num = 0;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			(*word_num)++;
			token = token->next;
			continue ;
		}
		if (token->kind == TK_OPERATOR \
			&& (*(token->str) == '>' || *(token->str) == '<'))
		{
			token = token->next->next;
			continue ;
		}
		break ;
	}
}

static int	set_node_argv(t_token **token, t_node *new)
{
	size_t	i;

	i = 0;
	while (i < new->word_num)
	{
		if ((*token)->kind != TK_WORD)
		{
			(*token) = ((*token)->next)->next;
			continue ;
		}
		new->argv[i++] = ft_strndup((*token)->str, (*token)->str_len);
		if (!new->argv[i - 1])
		{
			while (i)
				free(new->argv[--i]);
			return (free(new->argv), err_system_call("malloc"), ERR);
		}
		(*token) = (*token)->next;
	}
	while (consume_redirect(token, TK_OPERATOR, RD_APPEND) \
	|| consume_redirect(token, TK_OPERATOR, RD_HEREDOC) \
	|| consume_redirect(token, TK_OPERATOR, RD_IN) \
	|| consume_redirect(token, TK_OPERATOR, RD_OUT))
		(*token) = (*token)->next;
	return (SUCCESS);
}

// set redirection's info
static int	set_redirection(t_token *token, t_node *new)
{
	t_red	head;
	t_red	*cur;
	int		status;

	ft_bzero(&head, sizeof(t_red));
	cur = &head;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			token = token->next;
			continue ;
		}
		status = add_new_red(token, &cur);
		token = token->next->next;
		if (status < 0)
			return (status);
		else if (status == CMD_END)
			break ;
	}
	new->red = head.next;
	return (SUCCESS);
}

static int	add_new_red(t_token *token, t_red **cur)
{
	t_red		*new;
	t_RedKind	rkind;

	if (token->kind != TK_OPERATOR)
		return (CMD_END);
	if (!ft_strncmp(token->str, ">>", 2))
		rkind = RD_APPEND;
	else if (!ft_strncmp(token->str, "<<", 2))
		rkind = RD_HEREDOC;
	else if (*(token->str) == '<')
		rkind = RD_IN;
	else if (*(token->str) == '>')
		rkind = RD_OUT;
	else
		return (CMD_END);
	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (ERR);
	new->kind = rkind;
	new->file = ft_strndup(token->next->str, token->next->str_len);
	if (!new->file)
		return (free(new), ERR);
	(*cur)->next = new;
	(*cur) = new;
	return (SUCCESS);
}
