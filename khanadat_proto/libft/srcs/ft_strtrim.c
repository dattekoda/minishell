/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 07:18:20 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:32:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	isset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	begin(const char *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && isset(s1[i], set))
		i++;
	return (i);
}

static int	end(const char *s1, char const *set, int len, int start)
{
	int	i;

	i = len - 1;
	while (i > start && isset(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		len;
	int		start;
	int		goal;
	int		size;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	start = begin(s1, set);
	goal = end(s1, set, len, start);
	size = goal - start + 1;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + start, size);
	res[size] = '\0';
	return (res);
}
