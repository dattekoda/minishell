/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:28:31 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:36:15 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_define.h"
#include "status.h"
#include "libft.h"
#include "expand_define.h"
#include "search_dollar_utils.h"
#include "add_new_word_utils.h"

static void	classify_dollar(t_dollar **cur, t_mini *mini, char **tmp);

// found var then return value
// else return NULL
// push forward var
char	*mini_getenv(char **var, t_mini *mini)
{
	size_t	len;
	size_t	i;
	char	*chr;

	i = 0;
	chr = *var;
	while (**var && !ft_strchr("\'\"$/", **var))
		(*var)++;
	len = *var - chr;
	while (i < mini->envp_len)
	{
		if (!ft_strncmp(chr, mini->envp[i], len) \
		&& mini->envp[i][len] == '=')
			break ;
		i++;
	}
	if (!mini->envp[i])
		return (NULL);
	chr = ft_strchr(mini->envp[i], '=');
	if (chr)
		return (chr + 1);
	return (NULL);
}

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

int	search_dollar(t_word *word, t_mini *mini, t_dollar **dol)
{
	char		*tmp;
	t_dollar	head;
	t_dollar	*cur;

	ft_bzero(&head, sizeof(t_dollar));
	cur = &head;
	tmp = word->word;
	classify_dollar(&cur, mini, &tmp);
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
			*cur = add_dollar(*cur, mini, tmp, WD_DOLLAR);
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

t_word	*add_new_word(t_word *cur, t_dollar **dol)
{
	t_word		*new_word;
	t_dollar	*dol_tail;

	new_word = ft_calloc(1, sizeof(t_word));
	if (!new_word)
		return (NULL);
	dol_tail = *dol;
	new_word->word_len = count_word_len(dol);
	new_word->word = ft_calloc(new_word->word_len + 1, sizeof(char));
	cur->next = new_word;
	if (!new_word->word)
		return (free(new_word), NULL);
	set_word_word(new_word, dol_tail);
	return (new_word);
}
