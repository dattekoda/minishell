#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

typedef struct s_param
{
	char	*param;
	size_t	len;
}	t_param;

int		expand_params(char *line, char **expanded);
void	safe_free(char *ptr);

int main(void)
{
	char	*line;
	char	*expanded;

	line = NULL;
	expanded = NULL;
	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if (expand_params(line, &expanded))
			break ;
		printf("%s\n", expanded);
		free(line);
		free(expanded);
	}
	safe_free(line);
	safe_free(expanded);
	rl_clear_history();
	return (0);
}

void	param_free(void *ptr)
{
	t_param	*param;

	param = (t_param *)ptr;
	if (param && param->param)
		free(param->param);
	if (param)
		free(param);
}

int	skip_quotation(char *line, size_t *i)
{
	char	*chr;

	chr = NULL;
	if (line[*i] == '\'')
		chr = ft_strchr(&line[*i + 1], '\'');
	else if (line[*i] == '\"')
		chr = ft_strchr(&line[*i + 1], '\"');
	if (!chr)
	{
		fprintf(stderr, "syntax error\n");
		return (-1);
	}
	*i = (size_t)(chr - line + 1);
	return (0);
}

t_list	*t_paramnew(char *env_content)
{
	t_param	*param;

	param = ft_calloc(1, sizeof(t_param));
	if (!param)
		return (NULL);
	if (env_content)
		param->param = ft_strdup(env_content);
	else
		param->param = ft_strdup("");
	param->len = ft_strlen(param->param);
	return (ft_lstnew(param));
}

int	get_param(char *line, size_t *i, t_list **lst, size_t *dollar_len)
{
	char	*param_key;
	size_t	p_len;
	t_list	*newlst;

	(*i)++;
	p_len = *i;
	while (line[p_len] && !ft_isspace(line[p_len]) \
	&& line[p_len] != '\'' && line[p_len] != '\"')
		p_len++;
	param_key = ft_strndup(&line[*i], p_len - *i);
	*dollar_len += p_len - *i + 1;
	*i = p_len;
	if (!param_key)
		return (-1);
	newlst = t_paramnew(getenv(param_key));
	if (!newlst)
		return (free(param_key), -1);
	ft_lstadd_back(lst, newlst);
	return (free(param_key), 0);
}

int	search_params(char *line, t_list **lst, size_t *expanded_len)
{
	size_t	i;
	size_t	dollar_len;

	i = 0;
	dollar_len = 0;
	while(line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (skip_quotation(line, &i))
				return (-1);
		}
		else if (line[i] == '$' && (!i || (i && line[i - 1] != '\\')))
		{
			if (get_param(line, &i, lst, &dollar_len))
				return (-1);
		}
		else
			(i++);
	}
	*expanded_len = i - dollar_len;
	return (0);
}

size_t	calc_params_len(t_list *lst)
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

void	cpy_quotation(char *line, char *expanded, size_t *i, size_t *j)
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
size_t	cpy_param(char *line, t_list **lst, char *expanded, size_t *i)
{
	t_param	*param;
	size_t	len;

	param = (t_param *)((*lst)->content);
	len = param->len;
	ft_memmove(expanded, param->param, len);
	*lst = (*lst)->next;
	while (line[(*i)] && !ft_isspace(line[(*i)]) \
	&& line[(*i)] != '\'' && line[(*i)] != '\"')
		(*i)++;
	return (len);
}

int	store_expanded(char *line, t_list *lst, char **expanded, size_t expanded_len)
{
	size_t	i;
	size_t	j;

	expanded_len += calc_params_len(lst);
	// fprintf(stderr, "%zu\n", expanded_len);
	*expanded = calloc(expanded_len + 1, sizeof(char));
	if (!*expanded)
		return (-1);
	i = 0;
	j = 0;
	while(line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			cpy_quotation(line, *expanded, &i, &j);
		else if (line[i] == '$' && (!i || (i && line[i - 1] != '\\')))
			j += cpy_param(line, &lst, *expanded + j, &i);
		else
			(*expanded)[j++] = line[i++];
	}
	return (0);
}

int	expand_params(char *line, char **expanded)
{
	t_list	*lst;
	size_t	expanded_len;

	expanded_len = 0;
	lst = NULL;
	if (search_params(line, &lst, &expanded_len))
		return (ft_lstclear(&lst, param_free), -1);
	if (store_expanded(line, lst, expanded, expanded_len))
		return (ft_lstclear(&lst, param_free), -1);
	return (ft_lstclear(&lst, param_free), 0);
}

void	safe_free(char *ptr)
{
	if (ptr)
		free(ptr);
}
