/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:05:51 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/14 05:00:41 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"

static size_t	calc_params_len(t_list *lst);
static void		cpy_quotation(char *line, char *expanded, size_t *i, size_t *j);
static size_t	cpy_param(char *line, t_list **lst, char *expanded, size_t *i);

int	store_expanded(char *line, t_list *lst, \
	char **expanded, size_t expanded_len)
{
	size_t	i;
	size_t	j;

	expanded_len += calc_params_len(lst);
	*expanded = calloc(expanded_len + 1, sizeof(char));
	if (!*expanded)
		return (ERR);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			cpy_quotation(line, *expanded, &i, &j);
		else if (line[i] == '$')
			j += cpy_param(line, &lst, *expanded + j, &i);
		else
			(*expanded)[j++] = line[i++];
	}
	return (SUCCESS);
}

static size_t	calc_params_len(t_list *lst)
{
	size_t	params_len;

	params_len = 0;
	while (lst)
	{
		params_len += ((t_param *)(lst->content))->len;
		lst = lst->next;
	}
	return (params_len);
}

static void	cpy_quotation(char *line, char *expanded, size_t *i, size_t *j)
{
	if (line[*i] == '\'')
	{
		expanded[(*j)++] = line[(*i)++];
		while (line[*i] != '\'')
			expanded[(*j)++] = line[(*i)++];
	}
	else
	{
		expanded[(*j)++] = line[(*i)++];
		while (line[*i] != '\"')
			expanded[(*j)++] = line[(*i)++];
	}
	expanded[(*j)++] = line[(*i)++];
}

// return copied param's length
static size_t	cpy_param(char *line, t_list **lst, char *expanded, size_t *i)
{
	t_param	*param;
	size_t	param_len;

	param = (t_param *)((*lst)->content);
	param_len = param->len;
	ft_memmove(expanded, param->param, param_len);
	*lst = (*lst)->next;
	(*i)++;
	while (line[(*i)] && !ft_isspace(line[(*i)]) \
	&& !ft_strchr(SPECIALS, line[(*i)]))
		(*i)++;
	return (param_len);
}
