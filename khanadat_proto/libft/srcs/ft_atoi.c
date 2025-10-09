/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 06:18:52 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:31:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*nptr == ' ' || ('\t' <= *nptr && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		sign = -1 + 2 * (*(nptr++) == '+');
	while (*nptr && ft_isdigit(*nptr))
		num = num * 10 + (*(nptr++) - '0');
	return (sign * num);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(int argc, char* argv[])
// {
// 	if (argc == 1) return 0;
// 	printf("original: |%s|\n", argv[1]);
// 	printf("atoi:     |%d|\n", atoi(argv[1]));
// 	printf("ft_atoi:  |%d|\n", ft_atoi(argv[1]));
// 	return 0;
// }