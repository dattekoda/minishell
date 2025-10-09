/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:17:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 17:32:08 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define SUCCESS 0
#define NL_FOUND 1
#define NL_NOT_FOUND 0

void	safe_free(char **store)
{
	if (store && *store)
	{
		free(*store);
		*store = NULL;
	}
}

ssize_t	write_store(int fd, char **store)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	rd;

	if (!*store)
		*store = ft_strdup("");
	if (!*store)
		return (GNL_ERR_MALLOC);
	rd = 1;
	while (!ft_strchr(*store, '\n') && rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (safe_free(store), GNL_ERR_READ);
		if (rd == 0)
			break ;
		buf[rd] = '\0';
		tmp = ft_strjoin(*store, buf);
		safe_free(store);
		if (!tmp)
			return (GNL_ERR_MALLOC);
		*store = tmp;
	}
	return (rd);
}

int	get_line(char **line, char **store)
{
	char	*end_line;
	char	*rest;
	size_t	line_len;

	end_line = ft_strchr(*store, '\n');
	if (end_line)
	{
		line_len = (size_t)(end_line - *store) + 1;
		*line = ft_strndup(*store, line_len);
		if (!*line)
			return (GNL_ERR_MALLOC);
		rest = ft_strdup(end_line + 1);
		if (!rest)
			return (free(*line), GNL_ERR_MALLOC);
		safe_free(store);
		*store = rest;
	}
	else
	{
		*line = ft_strdup(*store);
		if (!*line)
			return (GNL_ERR_MALLOC);
		safe_free(store);
	}
	return (SUCCESS);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	*store = NULL;
	ssize_t		ws_ret;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (GNL_ERR_INVALID);
	*line = NULL;
	ws_ret = write_store(fd, &store);
	if (ws_ret < 0)
		return (ws_ret);
	if (ws_ret == 0 && (!store || !store[0]))
		return (safe_free(&store), GNL_EOF);
	if (get_line(line, &store))
		return (safe_free(&store), GNL_ERR_MALLOC);
	return (GNL_LINE);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char *argv[])
// {
// 	char	*line;
// 	int		gnl;
// 	int		fd;
// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	gnl = 1;
// 	while (gnl > 0)
// 	{
// 		gnl = ft_get_next_line(fd, &line);
// 		if (gnl < 0)
// 			break ;
// 		printf("gnl = %d\n%s", gnl, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char *argv[])
// {
// 	char	*line;
// 	int		gnl;
// 	int		fd;
// 	gnl = 1;
// 	while (gnl > 0)
// 	{
// 		gnl = ft_get_next_line(STDIN_FILENO, &line);
// 		if (gnl < 0)
// 			break ;
// 		if (gnl == 0)
// 			break ;
// 		printf("%d, %s", gnl, line);
// 		free(line);
// 	}
// 	return (0);
// }
