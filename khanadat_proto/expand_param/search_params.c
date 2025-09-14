/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:05:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/14 05:00:41 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "expand.h"

static int		skip_quotation(char *line, size_t *i);
static t_list	*t_paramnew(char *env_content);
static int		get_param(char *line, size_t *i, t_list **lst, \
	size_t *dollar_len);
static int		get_single_dollar(t_list **lst, size_t *dollar_len);

// count expanded_len and validate
int	search_params(char *line, t_list **lst, size_t *expanded_len)
{
	size_t	i;
	size_t	dollar_len;

	i = 0;
	dollar_len = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (skip_quotation(line, &i))
				return (ERR);
		}
		else if (line[i] == '$')
		{
			if (get_param(line, &i, lst, &dollar_len))
				return (ERR);
		}
		else
			(i++);
	}
	*expanded_len = i - dollar_len;
	return (SUCCESS);
}

static int	skip_quotation(char *line, size_t *i)
{
	char	*chr;

	chr = NULL;
	if (line[*i] == '\'')
		chr = ft_strchr(&line[*i + 1], '\'');
	else if (line[*i] == '\"')
		chr = ft_strchr(&line[*i + 1], '\"');
	if (!chr)
	{
		ft_putendl_fd("syntax_err", STDOUT_FILENO);
		return (ERR);
	}
	*i = (size_t)(chr - line + 1);
	return (SUCCESS);
}

static t_list	*t_paramnew(char *env_content)
{
	t_param	*node;

	node = ft_calloc(1, sizeof(t_param));
	if (!node)
		return (NULL);
	if (env_content)
		node->param = ft_strdup(env_content);
	else
		node->param = ft_strdup("");
	if (!node->param)
		return (free(node), NULL);
	node->len = ft_strlen(node->param);
	return (ft_lstnew(node));
}

static int	get_param(char *line, size_t *i, t_list **lst, \
	size_t *dollar_len)
{
	char	*env_name;
	size_t	start_point;
	t_list	*newlst;

	(*i)++;
	start_point = *i;
	while (line[*i] && !ft_isspace(line[*i]) \
	&& !ft_strchr(SPECIALS, line[*i]))
		(*i)++;
	if (*i == start_point)
		return (get_single_dollar(lst, dollar_len));
	env_name = ft_strndup(&line[start_point], *i - start_point);
	*dollar_len += *i - start_point + 1;
	if (!env_name)
		return (ERR);
	newlst = t_paramnew(getenv(env_name));
	if (!newlst)
		return (free(env_name), ERR);
	ft_lstadd_back(lst, newlst);
	return (free(env_name), SUCCESS);
}

static int	get_single_dollar(t_list **lst, \
	size_t *dollar_len)
{
	t_list	*newlst;

	*dollar_len += 1;
	newlst = t_paramnew("$");
	if (!newlst)
		return (ERR);
	ft_lstadd_back(lst, newlst);
	return (SUCCESS);
}
