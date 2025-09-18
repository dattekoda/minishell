/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:33:24 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/18 18:40:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_define.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/readline.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_node	*node;
	char	*line;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		if ()
	}
}
