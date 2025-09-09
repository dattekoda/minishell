/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:58:18 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/09 04:10:09 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ndup;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s_len < n)
		n = s_len;
	ndup = malloc(n + 1);
	if (!ndup)
		return (NULL);
	ft_memmove(ndup, s, n);
	ndup[n] = '\0';
	return (ndup);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	s[11] = "hel\nloworld";
// 	char	*t;

// 	t = ft_strndup(s, 4);
// 	printf("%s", t);
// 	return (free(t), 0);
// }