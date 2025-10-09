/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:58:54 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 15:18:38 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_define.h"
#include "ast_utils.h"
#include "minishell_define.h"
#include "tokenizer_define.h"
#include "libft.h"

static t_red		*add_new_red(t_red *cur, t_token *token, t_RedKind rkind);

void	free_red(t_red *head)
{
	t_red	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->file);
		free(head);
		head = tmp;
	}
}

int	set_redirection(t_token *token, t_node *new)
{
	t_red		head;
	t_red		*cur;
	t_RedKind	rkind;

	ft_bzero(&head, sizeof(t_red));
	cur = &head;
	while (token->kind != TK_EOF)
	{
		if (token->kind == TK_WORD)
		{
			token = token->next;
			continue ;
		}
		rkind = check_redkind(token);
		if (rkind == RD_NOT)
			break ;
		cur = add_new_red(cur, token, rkind);
		if (!cur)
			return (free_red(head.next), ERR);
		token = token->next->next;
	}
	new->red = head.next;
	return (SUCCESS);
}

static t_red	*add_new_red(t_red *cur, t_token *token, t_RedKind rkind)
{
	t_red		*new;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (NULL);
	new->kind = rkind;
	new->file = ft_strndup(token->next->str, token->next->str_len);
	if (!new->file)
		return (free(new), NULL);
	cur->next = new;
	return (new);
}

t_RedKind	check_redkind(t_token *token)
{
	if (!ft_strncmp(token->str, ">>", 2))
		return (RD_APPEND);
	if (!ft_strncmp(token->str, "<<", 2))
		return (RD_HEREDOC);
	if (*(token->str) == '>')
		return (RD_OUT);
	if (*(token->str) == '<')
		return (RD_IN);
	return (RD_NOT);
}
