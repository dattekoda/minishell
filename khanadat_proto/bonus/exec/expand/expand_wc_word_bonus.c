/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_word_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:11:52 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define_bonus.h"
#include "minishell_utils_bonus.h"
#include "ast_bonus.h"
#include "ast_define_bonus.h"
#include "expand_wc_utils_bonus.h"
#include "libft.h"
#include <dirent.h>

static t_word	*insert_wild_word(t_word *before, \
	t_word **word, t_word *cur);
static void		set_new_wild_word(char *expanded, t_word **new, DIR *dir_ptr);
static t_word	*add_new_wild_word(t_word **cur, char *d_name);

void	set_wild_word(t_mini *mini, t_word **word)
{
	t_word	*cur;
	t_word	*before;

	before = NULL;
	cur = *word;
	while (cur)
	{
		if (need_expand_wild(cur->wild_checker, cur->expanded, cur->exp_len))
			cur = insert_wild_word(before, word, cur);
		if (!cur)
			systemcall_minishell_exit(mini, "malloc");
		before = cur;
		cur = cur->next;
	}
}

static t_word	*insert_wild_word(t_word *before, \
	t_word **word, t_word *cur)
{
	t_word			head;
	t_word			*new;
	DIR				*dir_ptr;

	ft_bzero(&head, sizeof(t_word));
	new = &head;
	dir_ptr = opendir(CURRENT_DIR);
	if (!dir_ptr)
		return (cur);
	set_new_wild_word(cur->expanded, &new, dir_ptr);
	if (!new)
		return (free_word(head.next), NULL);
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

static void	set_new_wild_word(char *expanded, t_word **new, DIR *dir_ptr)
{
	struct dirent	*dirent_ptr;

	while (*new)
	{
		dirent_ptr = readdir(dir_ptr);
		if (!dirent_ptr)
			break ;
		if ((*expanded != '.' && *dirent_ptr->d_name == '.')
			|| !ft_strcmp("..", dirent_ptr->d_name) \
			|| !ft_strcmp(".", dirent_ptr->d_name))
			continue ;
		if (is_wildcard(expanded, dirent_ptr->d_name))
			*new = add_new_wild_word(new, dirent_ptr->d_name);
	}
	closedir(dir_ptr);
}

static t_word	*add_new_wild_word(t_word **cur, char *d_name)
{
	t_word	*new;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return (NULL);
	(*cur)->next = new;
	new->expanded = ft_strdup(d_name);
	if (!new->expanded)
		return (NULL);
	return (new);
}
