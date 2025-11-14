/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:48:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/11 18:27:14 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	static const size_t	res_size = 12;
	char				res[13];
	size_t				behind;
	bool				issigned;

	behind = (size_t)res_size;
	ft_bzero(res, res_size + 1);
	if (n == 0)
		return (ft_strdup("0"));
	issigned = (n < 0);
	if (issigned)
	{
		res[--behind] = (-1) * (n % 10) + '0';
		n = (-1) * (n / 10);
	}
	while (n)
	{
		res[--behind] = n % 10 + '0';
		n /= 10;
	}
	if (issigned)
		res[--behind] = '-';
	return (ft_strdup(res + behind));
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 		return 1;
// 	int a = ft_atoi(argv[1]);

// 	printf("%s\n", ft_itoa(a));
// 	return (0);
// }

/*
static int	count_digit(int n)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= (-1);
		digit += 1;
	}
	while (n != 0)
	{
		n /= 10;
		digit += 1;
	}
	return (digit);
}

static void	edge(char *res, int *n)
{
	if (*n == 0)
		res[0] = '0';
	if (*n == -2147483648)
	{
		res[1] = '2';
		*n = -147483648;
	}
	if (*n < 0)
	{
		res[0] = '-';
		*n *= (-1);
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = count_digit(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	edge(res, &n);
	len--;
	while (n > 0)
	{
		res[len--] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
*/