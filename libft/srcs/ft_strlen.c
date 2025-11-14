/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:04:42 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/09 04:07:19 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*h;

	h = s;
	while (*s)
		s++;
	return ((size_t)(s - h));
}

/*
#include <stdio.h>

int	main(int argc, char* argv[])
{
	if (argc == 1) return (0);
	printf("%d\n", ft_strlen(argv[1]));
	return (0);
}
*/