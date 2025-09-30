/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/21 09:59:00 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_define.h"
#include "libft.h"
#include "status.h"
#include "minishell_err.h"

t_token	*new_reserved_token(t_token *cur, char **str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (err_system_call("malloc"), NULL);
	cur->next = new;
	new->kind = TK_OPERATOR;
	new->str = *str;
	if (!ft_strncmp(*str, "||", 2) || !ft_strncmp(*str, "&&", 2) \
		|| !ft_strncmp(*str, "<<", 2) || !ft_strncmp(*str, ">>", 2))
		(*str) += 2;
	else if (**str == '|' || **str == '>' || **str == '<')
		(*str)++;
	new->str_len = (size_t)((*str) - new->str);
	return (new);
}

int	skip_word(char **str)
{
	char	*chr;

	while (**str)
	{
		if (**str == '\'' || **str == '\"')
		{
			chr = ft_strchr(*str + 1, **str);
			if (!chr)
				return (put_syntax_err(**str), ERR);
			*str = chr + 1;
			continue ;
		}
		if (ft_isspace(**str) || ft_strchr(SPECIAL_CHAR, **str))
			break ;
		(*str)++;
	}
	return (SUCCESS);
}

t_token	*new_word_token(t_token *cur, char **str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (err_system_call("malloc"), NULL);
	new->kind = TK_WORD;
	cur->next = new;
	new->str = *str;
	if (skip_word(str))
		return (NULL);
	new->str_len = (size_t)((*str) - new->str);
	return (new);
}

t_token	*new_eof_token(t_token *cur)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->kind = TK_EOF;
	cur->next = new;
	return (new);
}
