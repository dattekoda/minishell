/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:15:50 by khanadat          #+#    #+#             */
/*   Updated: 2025/07/17 16:29:01 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_abs(int a)
{
	if (a > 0)
		return (a);
	return (-a);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(int argc, char *argv[])
// {
// 	if (argc < 2)
// 		return (0);
// 	int	i = ft_atoi(argv[1]);
// 	if (!ft_strcmp(ft_itoa(ft_abs(i)), ft_itoa(abs(i))))
// 		ft_putendl_fd("ok", STDOUT_FILENO);
// 	else
// 		ft_putendl_fd("false", STDERR_FILENO);
// 	return (0);
// }