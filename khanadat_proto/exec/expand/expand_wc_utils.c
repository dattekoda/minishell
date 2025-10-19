/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:29:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 14:31:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>

bool	need_expand_wild(bool *wild_checker, char *expanded, size_t exp_len)
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

bool	is_wildcard(char *pattern, char *d_name)
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
