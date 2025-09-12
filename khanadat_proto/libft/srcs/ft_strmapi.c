/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:39:44 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/23 20:32:44 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len)
		res[i] = f((unsigned int) i, s[i]);
	res[len] = '\0';
	return (res);
}
