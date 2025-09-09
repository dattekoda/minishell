/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:55:20 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/09 14:45:23 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			*(d + n) = *(s + n);
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