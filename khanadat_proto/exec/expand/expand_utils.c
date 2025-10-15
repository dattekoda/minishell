/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iokuno <iokuno@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:28:31 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 22:28:12 by iokuno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classify_utils.h"
#include "expand_define.h"
#include "libft.h"
#include "minishell_define.h"
#include <stdlib.h>

static void	classify_dollar(t_dollar **cur, t_mini *mini, char **tmp);

void	free_dollar(t_dollar *head)
{
	t_dollar	*tmp;

	while (head)
	{
		tmp = (head)->next;
		free(head);
		head = tmp;
	}
}

int	get_dollar(char *file, t_mini *mini, t_dollar **dol)
{
	t_dollar	head;
	t_dollar	*cur;

	ft_bzero(&head, sizeof(t_dollar));
	cur = &head;
	head.dkind = WD_HEAD;
	classify_dollar(&cur, mini, &file);
	if (!cur)
		return (free_dollar(head.next), ERR);
	*dol = head.next;
	return (SUCCESS);
}

static void	classify_dollar(t_dollar **cur, t_mini *mini, char **tmp)
{
	while (**tmp && *cur)
	{
		if (**tmp == '$')
		{
			*cur = classify_more_dollar(cur, mini, tmp);
			continue ;
		}
		if (**tmp == '\'')
		{
			*cur = add_single(*cur, tmp);
			continue ;
		}
		if (**tmp == '\"')
		{
			*cur = classify_double(cur, mini, tmp);
			continue ;
		}
		*cur = add_outside(*cur, tmp);
	}
}
