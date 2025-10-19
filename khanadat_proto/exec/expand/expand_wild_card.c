/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wild_card.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:11:52 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 13:43:19 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define.h"
#include "minishell_utils.h"
#include "ast.h"
#include "ast_define.h"
#include "libft.h"
#include <dirent.h>

static bool		need_expand_wild(bool *wild_checker, char *expanded, size_t exp_len);
static t_word	*insert_wild_word(t_mini *mini, t_word *before, t_word **word, t_word *cur);
static bool		is_wildcard(char *pattern, char *d_name);
static t_word	*add_new_wild(t_word *cur, char *d_name);

void	set_wild_word(t_mini *mini, t_word **word)
{
	t_word	*cur;
	t_word	*before;

	before = NULL;
	cur = *word;
	while (cur)
	{
		if (need_expand_wild(cur->wild_checker, cur->expanded, cur->exp_len))
			cur = insert_wild_word(mini, before, word, cur);
		before = cur;
		cur = cur->next;
	}
}

static bool	need_expand_wild(bool *wild_checker, char *expanded, size_t exp_len)
{
	size_t	i;
	bool	need;

	i = 0;
	need = false;
	while (i < exp_len)
	{
		if (!wild_checker[i] && expanded[i] == '*')
			return (false);
		if (wild_checker[i] && expanded[i] == '*')
			need = true;
		i++;
	}
	return (need);
}

static t_word	*insert_wild_word(t_mini *mini, t_word *before, t_word **word, t_word *cur)
{
	t_word			head;
	t_word			*new;
	DIR				*dir_ptr;
	struct dirent	*dirent_ptr;

	ft_bzero(&head, sizeof(t_word));
	new = &head;
	dir_ptr = opendir(".");
	if (!dir_ptr)
		return (cur);
	while (new)
	{
		dirent_ptr = readdir(dir_ptr);
		if (!dirent_ptr)
		break ;
		if ((*cur->expanded != '.' && *dirent_ptr->d_name == '.')
		||	!ft_strcmp("..", dirent_ptr->d_name) \
		|| !ft_strcmp(".", dirent_ptr->d_name))
		continue ;
		if (is_wildcard(cur->expanded, dirent_ptr->d_name))
			new = add_new_wild(new, dirent_ptr->d_name);
	}
	closedir(dir_ptr);
	if (!new)
	{
		free_word(head.next);
		systemcall_minishell_exit(mini, "malloc");
	}
	if (!head.next)
		return (cur);
	if (before)
		before->next = head.next;
	else
		(*word) = head.next;
	new->next = cur->next;
	cur->next = NULL;
	free_word(cur);
	return (new);
}

static bool	is_wildcard(char *pattern, char *d_name)
{
	if (!*pattern)
		return (!*d_name);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (true);
		while (*d_name)
		{
			if (is_wildcard(pattern, d_name))
				return (true);
			d_name++;
		}
	}
	if (*d_name && *pattern == *d_name)
		return (is_wildcard(pattern + 1, d_name + 1));
	return (false);
}

static t_word	*add_new_wild(t_word *cur, char *d_name)
{
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return (NULL);
	cur->next = new;
	new->expanded = ft_strdup(d_name);
	if (!new->expanded)
		return (NULL);
	return (new);
}
