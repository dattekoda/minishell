/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 03:11:06 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/11 18:27:45 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	copy_len;
	size_t	s_len;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		copy_len = len;
	else
		copy_len = s_len - start;
	sub = malloc(copy_len + 1);
	if (!sub)
		return (NULL);
	ft_memmove(sub, s + start, copy_len);
	sub[copy_len] = '\0';
	return (sub);
}
