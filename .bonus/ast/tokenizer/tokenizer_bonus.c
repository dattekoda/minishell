/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:51 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_err_bonus.h"
#include "tokenizer_define_bonus.h"
#include "tokenizer_utils_bonus.h"
#include "libft.h"

static int	ready_4_get_token(t_token **token, char *line, \
	t_token *head, t_token **cur);

void	free_token(t_token **token)
{
	t_token	*tmp;

	while ((*token))
	{
		tmp = (*token)->next;
		free((*token));
		(*token) = tmp;
	}
	(*token) = NULL;
}

// if systemcall err return -1
// if syntax err like ' was not enclosed return 2
// @token is set tokenized pointer
// @line receive a raw information from prompt.
int	get_token(t_token **token, char *line)
{
	t_token	head;
	t_token	*cur;

	if (ready_4_get_token(token, line, &head, &cur))
		return (SYNTAX_ERR);
	while (*line && cur)
	{
		if (ft_isspace(*line))
		{
			line++;
			continue ;
		}
		if (ft_strchr(SPECIAL_CHAR, *line))
		{
			cur = new_op_token(cur, &line);
			continue ;
		}
		cur = new_word_token(cur, &line);
	}
	if (!cur || !new_eof_token(cur))
		return (free_token(&head.next), ERR);
	*token = head.next;
	return (SUCCESS);
}

static int	ready_4_get_token(t_token **token, char *line, \
	t_token *head, t_token **cur)
{
	*token = NULL;
	ft_bzero(head, sizeof(t_token));
	if (validate_b4_tokenize(line))
		return (SYNTAX_ERR);
	*cur = head;
	return (SUCCESS);
}
