/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_validate_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:54 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell_define_bonus.h"
#include "minishell_err_bonus.h"

static int	validate_quote(const char *line);
static int	valitate_and(const char *line);
static int	validate_parenthesis(const char *line);

int	validate_b4_tokenize(const char *line)
{
	if (validate_quote(line))
		return (SYNTAX_ERR);
	if (valitate_and(line))
		return (SYNTAX_ERR);
	if (validate_parenthesis(line))
		return (SYNTAX_ERR);
	return (SUCCESS);
}

static int	validate_quote(const char *line)
{
	char	*tmp;

	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			tmp = ft_strchr(line + 1, *line);
			if (!tmp)
				return (put_syntax_err(*line), SYNTAX_ERR);
			line = tmp + 1;
			continue ;
		}
		line++;
	}
	return (SUCCESS);
}

static int	valitate_and(const char *line)
{
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line = ft_strchr(line + 1, *line);
		if (*line == '&')
		{
			if (*(line + 1) != '&')
				return (put_syntax_err('&'), SYNTAX_ERR);
			line++;
		}
		line++;
	}
	return (SUCCESS);
}

// check if enclosed with parenthesis correctly
static int	validate_parenthesis(const char *line)
{
	int	checker;

	checker = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line = ft_strchr(line + 1, *line);
		if (*line == '(')
			checker++;
		if (*line == ')')
			checker--;
		if (checker < 0)
			return (put_syntax_err(')'), SYNTAX_ERR);
		line++;
	}
	if (checker == 0)
		return (SUCCESS);
	return (put_syntax_err('('), SYNTAX_ERR);
}

// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	if (argc == 1)
// 		return 1;
// 	if (!validate_parenthesis(argv[1]))
// 		printf("valid\n");
// }
