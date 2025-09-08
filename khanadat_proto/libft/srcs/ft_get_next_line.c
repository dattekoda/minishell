/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:17:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/08 15:59:49 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif

// typedef struct s_gnl
// {
// 	char	*str;
// 	size_t	head;
// 	size_t	tail;
// }	t_gnl;

#define ERR_INVALID -3
#define ERR_MALLOC -2
#define ERR_READ -1
#define SUCCESS 0
#define GNL_EOF 0
#define GNL_LINE 1
#define NL_FOUND 1
#define NL_NOT_FOUND 0

int	write_store(int fd, char **store)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	rd;

	if (!*store)
		*store = ft_strdup("");
	if (!*store)
		return (ERR_MALLOC);
	rd = 1;
	while (!ft_strchr(*store, '\n') && 0 < rd)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (free(*store), ERR_READ);
		buf[rd] = 0;
		tmp = ft_strjoin(*store, buf);
		free(*store);
		if (!tmp)
			return (ERR_MALLOC);
		*store = tmp;
	}
	return (SUCCESS);
}

int	get_line(char **line, char **store)
{
	char	*end_line;
	size_t	line_len;

	end_line = ft_strchr(*store, '\n');
	if (end_line)
	{
		line_len = end_line - *store + 1;
		*line = ft_strndup(*store, line_len);
		if (!*line)
			return (ERR_MALLOC);
		ft_memmove(*store, end_line + 1, ft_strlen(end_line + 1) + 1);
	}
	else
	{
		*line = ft_strdup(*store);
		if (!*line)
			return (ERR_MALLOC);
		(*store)[0] = 0;
	}
	return (SUCCESS);
}

int	ft_get_next_line(int fd, char **line)
{
	static char	*store = NULL;
	int			ws_ret;

	*line = NULL;
	ws_ret = write_store(fd, &store);
	if (ws_ret)
		return (ws_ret);
	if (!store[0])
		return (free(store), GNL_EOF);
	if (get_line(line, &store))
		return (free(store), ERR_MALLOC);
	return (GNL_LINE);
}

// static ssize_t	free_return(char **str, ssize_t output);
// static ssize_t	read_to_str(int fd, t_gnl *gnl);
// static char		*get_line(t_gnl *gnl);

// //set fd = GNL_FREE_FD and you can free(gnl.str)
// int	ft_get_next_line(int fd, char **line)
// {
// 	static t_gnl	gnl = {NULL, 0, -1};
// 	int				rd;

// 	if (!gnl.str)
// 		gnl.str = ft_strdup("");
// 	if (!gnl.str)
// 		return (ERR_MALLOC);
// 	if (fd == GNL_FREE_FD)
// 		return (free_return(&gnl.str, GNL_EOF));
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (free_return(&gnl.str, ERR_INVALID));
// 	rd = read_to_str(fd, &gnl);
// 	if (rd < 0)
// 		return (rd);
// 	*line = get_line(&gnl);
// 	if (rd == 0)
// 		return (free_return(&gnl.str, GNL_EOF));
// 	if (*line)
// 		return (GNL_LINE);
// 	return (ERR_MALLOC);
// }

// static ssize_t	free_return(char **str, ssize_t output)
// {
// 	if (*str)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// 	return (output);
// }

// static ssize_t	read_to_str(int fd, t_gnl *gnl)
// {
// 	ssize_t	rd;
// 	char	*tmp;
// 	char	*buf;

// 	rd = 1;
// 	buf = malloc(BUFFER_SIZE + 1);
// 	if (!buf)
// 		return (free_return(&gnl->str, ERR_MALLOC));
// 	while (!ft_strchr(gnl->str + gnl->head, '\n') && rd > 0)
// 	{
// 		rd = read(fd, buf, BUFFER_SIZE);
// 		if (rd < 0)
// 			return (free(buf), free_return(&gnl->str, ERR_READ));
// 		buf[rd] = '\0';
// 		tmp = gnl->str;
// 		gnl->str = ft_strjoin(tmp, buf);
// 		free(tmp);
// 		if (!gnl->str)
// 			return (free_return(&buf, ERR_MALLOC));
// 	}
// 	if (!gnl->str)
// 		return (free_return(&buf, ERR_MALLOC));
// 	return (free_return(&buf, rd));
// }

// static char	*get_line(t_gnl *gnl)
// {
// 	char	*nl;
// 	char	*line;

// 	nl = ft_strchr(gnl->str + gnl->head, '\n');
// 	if (!nl)
// 		nl = gnl->str + ft_strlen(gnl->str);
// 	gnl->tail = nl - gnl->str;
// 	line = ft_strndup(gnl->str + gnl->head, gnl->tail - gnl->head + 1);
// 	gnl->head = gnl->tail + 1;
// 	return (line);
// }

#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char *argv[])
{
	char	*line;
	int		gnl;
	int		fd;
	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	gnl = 1;
	while (gnl > 0)
	{
		gnl = ft_get_next_line(fd, &line);
		if (gnl < 0)
			break ;
		printf("gnl = %d\n%s", gnl, line);
		free(line);
	}
	close(fd);
	return (0);
}

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
