/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:51 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/28 10:59:55 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "status.h"
#include "minishell_err.h"
#include "tokenizer_define.h"
#include "tokenizer_utils.h"
#include "libft.h"

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

	*token = (ft_bzero(&head, sizeof(t_token)), NULL);
	if (validate_b4_tokenize(line))
		return (SYNTAX_ERR);
	cur = &head;
	while (*line && cur)
	{
		if (ft_isspace(*line))
		{
			line++;
			continue ;
		}
		if (ft_strchr(SPECIAL_CHAR, *line))
		{
			cur = new_reserved_token(cur, &line);
			continue ;
		}
		cur = new_word_token(cur, &line);
	}
	if (!cur || !new_eof_token(cur))
		return (free_token(&head.next), ERR);
	*token = head.next;
	return (SUCCESS);
}
