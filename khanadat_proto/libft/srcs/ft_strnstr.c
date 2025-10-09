/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:03:02 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:32:47 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (i + j < len
			&& big[i + j] && little[j]
			&& big[i + j] == little[j])
			j++;
		if (!(little[j]))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *s1 = "see FF your FF return FF now FF";
// 	char *s2 = "FF";
// 	size_t max = ft_strlen(s1);
// 	char *i1 = strnstr(s1, s2, max);
// 	char *i2 = ft_strnstr(s1, s2, max);
// 	if (i1 == i2)
// 		printf("success\n");
// 	else
// 		printf("failed\n");
// 	return (0);
// }