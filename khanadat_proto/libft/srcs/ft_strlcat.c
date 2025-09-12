/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:50:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:33:24 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*h;

	h = s;
	while (maxlen && *s)
	{
		maxlen--;
		s++;
	}
	return (s - h);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strnlen(dst, size);
	src_len = ft_strlen(src);
	dst += dst_len;
	size -= dst_len;
	while (1 < size && *src)
		*dst++ = (size--, *src++);
	if (size)
		*dst = 0;
	return (dst_len + src_len);
}

/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{
	char dst[] = "012345678\0";
	char dst1[] = "012345678\0";
	char src[] = "abcdefghijk";

	dst[sizeof(dst) - 1] = '\0';
	dst1[sizeof(dst1) - 1] = '\0';
	size_t ft = ft_strlcat(dst, src, sizeof(dst));
	size_t real = strlcat(dst1, src, sizeof(dst1));
	printf("ft:%zu\n", ft);
	printf("real: %zu\n", real);
	printf("%s\n", dst);
	printf("%s\n", dst1);
	return (0);
}*/