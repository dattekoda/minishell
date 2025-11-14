/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:47:17 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:32:21 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) s;
	while (n--)
		*p++ = (unsigned char) c;
	return (s);
}

/*
#include <stdio.h>

int main(void) {
    char   ohayo[10];
    ft_memset(ohayo, 'a', 5);
    printf("%s\n", ohayo);
    return 0;
}*/