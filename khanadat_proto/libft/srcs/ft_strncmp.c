/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:26:12 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/09 14:53:40 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n-- == 0)
		return (0);
	while (n-- && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	printf("real: %d\n", strncmp(argv[1], argv[2], atoi(argv[3])));
// 	printf("ft:   %d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
// }