/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:00:23 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/09 15:17:26 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_lib.h"
#include "libft.h"

#define FILENAME_DAFAULT_LEN 13
#define HEREDOC_FILENAME "/tmp/.heredoc"

char	*set_heredoc_name(int num)
{
	char	file_name[FILENAME_MAX];
	int		i;
	int		tmp;

	tmp = num;
	ft_strlcpy(file_name, HEREDOC_FILENAME, FILENAME_MAX);
	i = FILENAME_DAFAULT_LEN;
	if (tmp == 0)
		file_name[i++] = '0';
	while (tmp)
	{
		file_name[i++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	file_name[i] = '\0';
	num++;
	if (!access(file_name, F_OK))
		return (set_heredoc_name(num));
	return (ft_strdup(file_name));
}

static void	expand_dollar_ready(t_mini *mini, char *line, \
	size_t *expanded_size, t_list *list)
{
	char	*env_val;

	*expanded_size = 0;
	while (*line)
	{
		if (*line == '$')
		{
			line++;
			env_val = mini_getenv(&line, mini);
			ft_lstadd_back(&list, \
				ft_lstnew(env_val));
			(*expanded_size) += ft_strlen(env_val);
			continue ;
		}
		ft_lstadd_back(&list, ft_lstnew(line));
		while (*line && *line != '$')
		{
			(*expanded_size)++;
			line++;
		}
	}
}

static void	expand_dollar_set(t_list *list, char *expanded)
{
	size_t	i;
	t_list	*tmp;
	char	*cur;

	i = 0;
	while (list)
	{
		cur = (char *)list->content;
		while (*cur && *cur != '$')
			expanded[i++] = *(cur++);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int	expand_dollar(t_mini *mini, char **line)
{
	char	*expanded;
	size_t	expanded_size;
	t_list	*list;
	t_list	head;

	if (!ft_strchr(*line, '$'))
		return (SUCCESS);
	ft_bzero(&head, sizeof(t_list));
	list = &head;
	expand_dollar_ready(mini, *line, &expanded_size, list);
	expanded = ft_calloc(expanded_size + 1, sizeof(char));
	if (!expanded)
	{
		ft_lstclear(&head.next, NULL);
		systemcall_minishell_exit(mini, "malloc");
	}
	list = head.next;
	expand_dollar_set(list, expanded);
	free(*line);
	*line = expanded;
	return (SUCCESS);
}
