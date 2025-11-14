/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 05:21:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:33:19 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	char	nstr[12];
	int		len;
	int		i;

	len = count_digit(n);
	nstr[len] = '\0';
	edge(nstr, &n);
	i = len - 1;
	while (n > 0)
	{
		nstr[i--] = n % 10 + '0';
		n /= 10;
	}
	ft_putstr_fd(nstr, fd);
}
