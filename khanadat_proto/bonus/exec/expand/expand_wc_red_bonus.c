/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_red_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:41:12 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:55:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_define_bonus.h"
#include "minishell_err_bonus.h"
#include "minishell_utils_bonus.h"
#include "ast_bonus.h"
#include "ast_define_bonus.h"
#include "expand_wc_utils_bonus.h"
#include "libft.h"
#include <stdbool.h>
#include <dirent.h>

t_red			*insert_wild_red(t_red *before, t_red **red, \
	t_red *cur, bool *ambigous);
static void		set_new_wild_red(t_red *orig, t_red **new, \
	DIR *dir_ptr, bool *ambigous);
static t_red	*add_new_wild_red(t_red *orig, t_red **cur, \
	char *d_name);

int	set_wild_red(t_mini *mini, t_red **red)
{
	t_red	*cur;
	t_red	*before;
	bool	ambigous;

	before = NULL;
	cur = *red;
	ambigous = false;
	while (cur)
	{
		if (need_expand_wild(cur->wild_checker, cur->expanded, cur->exp_len))
			cur = insert_wild_red(before, red, cur, &ambigous);
		if (!cur)
			systemcall_minishell_exit(mini, "malloc");
		if (ambigous)
			return (err_ambiguous(cur->file), FAILURE);
		before = cur;
		cur = cur->next;
	}
	return (SUCCESS);
}

t_red	*insert_wild_red(t_red *before, t_red **red, \
	t_red *cur, bool *ambigous)
{
	t_red	head;
	t_red	*new;
	DIR		*dir_ptr;

	ft_bzero(&head, sizeof(t_red));
	new = &head;
	dir_ptr = opendir(CURRENT_DIR);
	if (!dir_ptr)
		return (cur);
	set_new_wild_red(cur, &new, dir_ptr, ambigous);
	if (!new)
		return (free_red(head.next), NULL);
	if (!head.next || *ambigous)
		return (free_red(head.next), cur);
	if (before)
		before->next = head.next;
	else
		(*red) = head.next;
	new->next = cur->next;
	cur->next = NULL;
	free_red(cur);
	return (new);
}

static void	set_new_wild_red(t_red *orig, t_red **new, \
	DIR *dir_ptr, bool *ambigous)
{
	struct dirent	*dirent_ptr;
	int				i;

	i = 0;
	while (*new)
	{
		dirent_ptr = readdir(dir_ptr);
		if (!dirent_ptr)
			break ;
		if ((*(orig->expanded) != '.' && *dirent_ptr->d_name == '.')
			|| !ft_strcmp("..", dirent_ptr->d_name) \
			|| !ft_strcmp(".", dirent_ptr->d_name))
			continue ;
		if (is_wildcard(orig->expanded, dirent_ptr->d_name))
		{
			*new = add_new_wild_red(orig, new, dirent_ptr->d_name);
			i++;
		}
	}
	closedir(dir_ptr);
	if (1 < i)
		*ambigous = true;
}

static t_red	*add_new_wild_red(t_red *orig, t_red **cur, char *d_name)
{
	t_red	*new;

	new = ft_calloc(1, sizeof(t_red));
	if (!new)
		return (NULL);
	ft_memmove(new, orig, sizeof(t_red));
	(*cur)->next = new;
	new->expanded = ft_strdup(d_name);
	new->exp_len = ft_strlen(d_name);
	new->wild_checker = NULL;
	new->next = NULL;
	return (new);
}
