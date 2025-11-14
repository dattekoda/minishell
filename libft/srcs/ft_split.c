/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 08:57:38 by khanadat          #+#    #+#             */
/*   Updated: 2025/06/28 15:04:27 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	char	**_split;

	split = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	_split = split;
	while (split && *s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		*split = (char *) s;
		while (*s && *s != c)
			s++;
		*split = ft_substr(*split, 0, s - *split);
		if (!*split++)
		{
			while (_split != split - 1)
				free(*(--split - 1));
			return (free(_split), NULL);
		}
	}
	return (_split);
}

// static int	count(char const *s, char c)
// {
// 	int	output;

// 	output = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if(!*s)
// 			break ;
// 		output++;
// 		while (*s && *s != c)
// 			s++;
// 	}
// 	return (output);
// }

// static void	measure_sizes(char const *s, char c, int *res_sizes)
// {
// 	int	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (!*s)
// 			break ;
// 		res_sizes[i] = 0;
// 		while (*s && *s != c)
// 		{
// 			res_sizes[i]++;
// 			s++;
// 		}
// 		i++;
// 	}
// }

// static int	fill_words(char const *s, char c, char **res, int *res_sizes)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (!(*s))
// 			break ;
// 		j = 0;
// 		res[i] = malloc(res_sizes[i] + 1);
// 		if (!res[i])
// 		{
// 			while (i-- > 0)
// 				free(res[i]);
// 			free(res);
// 			return (0);
// 		}
// 		while (*s && *s != c)
// 			res[i][j++] = *s++;
// 		res[i++][j] = '\0';
// 	}
// 	return (1);
// }

// static char	**init_split(char const *s, char c, int *wc, int **sizes)
// {
// 	char	**res;

// 	*wc = count(s, c);
// 	res = malloc(sizeof(char *) * (*wc + 1));
// 	if (!res)
// 		return (NULL);
// 	if (*wc > 0)
// 	{
// 		*sizes = malloc(sizeof(int) * (*wc));
// 		if (!*sizes)
// 		{
// 			free(res);
// 			return (NULL);
// 		}
// 		measure_sizes(s, c, *sizes);
// 	}
// 	return (res);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**res;
// 	int		word_count;
// 	int		*res_sizes;

// 	if (!s)
// 		return (NULL);
// 	res = init_split(s, c, &word_count, &res_sizes);
// 	if (!res)
// 		return (NULL);
// 	if (word_count > 0 && !fill_words(s, c, res, res_sizes))
// 	{
// 		free(res_sizes);
// 		return (NULL);
// 	}
// 	res[word_count] = NULL;
// 	if (word_count > 0)
// 		free(res_sizes);
// 	return (res);
// }

// #include <stdio.h>

// int main(int argc, char* argv[])
// {
// 	char	**words;
// 	int		i = 0;

// 	if (argc == 1)
// 		words = ft_split(" fjfkdasjfd  f dasjfkda lfd adfl a", ' ');
// 	else
// 		words = ft_split(argv[1], argv[2][0]);
// 	while (words[i])
// 		printf("%s\n", words[i++]);
// 	return (0);
// }