/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:55:20 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:33:16 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	if (n == 0 || dest == src)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char a[10] = "ohayo";
// 	char b[10] = "sayonara";
// 	ft_memmove((void *)(a + 1), (void *)b, 10);
// 	printf("%s\n", a);
// 	return (0);
// }