/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:54 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/21 09:58:55 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "status.h"
#include "minishell_err.h"

static int	syntax_quote_validate(char *line);
static int	syntax_and_valitate(char *line);

int	validate_b4_tokenize(char *line)
{
	if (syntax_quote_validate(line) \
	|| syntax_and_valitate(line))
		return (SYNTAX_ERR);
	return (SUCCESS);
}

static int	syntax_quote_validate(char *line)
{
	char	*tmp;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			tmp = ft_strchr(line + 1, *line);
			if (!tmp)
				return (put_syntax_err('\''), SYNTAX_ERR);
			line = tmp + 1;
			continue ;
		}
		line++;
	}
	return (SUCCESS);
}

static int	syntax_and_valitate(char *line)
{
	char	*tmp;

	while (*line)
	{
		tmp = ft_strchr(line, '&');
		if (!tmp)
			break ;
		if (*(tmp + 1) != '&')
			return (put_syntax_err('&'), SYNTAX_ERR);
		line = tmp + 2;
	}
	return (SUCCESS);
}
