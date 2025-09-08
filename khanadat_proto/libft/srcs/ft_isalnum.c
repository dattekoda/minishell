/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:42:02 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:33:06 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int c)
{
	if (('0' <= c && c <= '9')
		|| ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z'))
		return (8);
	return (0);
}

/*
int	main(void)
{
	if (isalnum('a'))
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}
	return (0);
}
*/