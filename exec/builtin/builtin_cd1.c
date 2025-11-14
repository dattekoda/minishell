/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:43:57 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/13 18:00:27 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_err.h"
#include "minishell_utils.h"
#include "builtin_cd_utils.h"
#include "libft.h"

static void	change_to_parent_dir(char *path, size_t *i);

int	chdir_parent(t_mini *mini)
{
	char	*parent_dir;
	size_t	i;
	int		status;

	parent_dir = normal_getenv(ENV_PWD, mini);
	if (!parent_dir)
		return (err_cd_getcwd(), FAILURE);
	change_to_parent_dir(parent_dir, &i);
	status = chdir(parent_dir);
	if (i)
		parent_dir[i] = '/';
	if (status < 0)
		return (err_cd(".."), FAILURE);
	return (SUCCESS);
}

static void	change_to_parent_dir(char *path, size_t *i)
{
	char	*tail;

	*i = 0;
	tail = path + ft_strlen(path) - 1;
	while (tail != path && *tail == '/')
		*(tail--) = '\0';
	tail = ft_strrchr(path, '/');
	if (!tail)
		return ;
	if (path == tail)
		return ;
	*i = tail - path;
	*tail = '\0';
}

// #include <stdio.h>
// int	main(int argc, char *argv[])
// {
// 	if (argc == 1)
// 		return 1;
// 	char *path = ft_strdup(argv[1]);
// 	size_t	i;
// 	change_to_parent_dir(path, &i);
// 	printf("%s\n", path);
// 	if (i)
// 		path[i] = '/';
// 	printf("%s\n", path);
// 	return (0);
// }
