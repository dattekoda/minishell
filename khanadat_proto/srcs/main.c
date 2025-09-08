/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:28:16 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/08 22:26:33 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "define.h"
#include <unistd.h>
#include <stdlib.h>
#define INSIDE_DOUBLE 1
#define INSIDE_SINGLE 2
#define DEFAULT 0

void	count_num_cmds(t_prompt *prompt)
{
	char	*line;
	int		status;

	status = DEFAULT;
	line = prompt->cmd_line;
	while (*line)
	{
		while (ft_strchr(" \t", *line))
			*line++;
		if (*line == '\"')
		{
			line = ft_strchr(line, '\"');
			if (!line)
				msg_syntax_err();
		}
		if (*line == '\'')
			line = ft_strchr(line, '\'');
		if (!line)
			msg_syntax_err()
		if ((status == INSIDE_DOUBLE && *line == '\"') \
		|| (status == INSIDE_SINGLE && *line == '\''))
			status = DEFAULT;
		if (*line == '|' && *(line + 1) != '|')
			line += 2;
	}
}

void	set_prompt(t_prompt *prompt)
{
	ft_memset(prompt, 0, sizeof(t_prompt));
	count_num_cmds(prompt);
}

void	get_prompt(t_prompt *prompt)
{
	int	gnl;

	gnl = ft_get_next_line(STDIN_FILENO, &prompt->prompt);
	if (gnl < 0)
		exit(gnl);
	set_prompt(prompt);
}

void	display_prompt(char *shell_name)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
}

int	main(int argc, char *argv[], char *env[])
{
	t_prompt	prompt;
	t_arg		arg;

	arg = (t_arg){argc, argv, env};
	prompt.arg = &arg;
	prompt.shell_name = argv[0];
	while (1)
	{
		display_prompt(prompt.shell_name);
		get_prompt(&prompt);
		exec_prompt(&prompt);
	}
}
