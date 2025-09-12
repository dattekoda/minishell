/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:28:16 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/10 02:08:49 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "define.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define INSIDE_DOUBLE 1
#define INSIDE_SINGLE 2
#define DEFAULT 0

#define END_STATUS 127

void	exit_shell(void)
{
	write(STDERR_FILENO, "exit\n", 5);
	exit(END_STATUS);
}

void	msg_err(const char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd((char *)msg, STDERR_FILENO);
}

void	msg_syntax_err(void)
{
	ft_putendl_fd("syntax error", STDERR_FILENO);
}

void	count_words(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->cmd_line[++i])
	{
		while (prompt->cmd_line[i] == ' ' \
		|| prompt->cmd_line[i] == '\t' \
		&& prompt->cmd_line[i] == '\n')
			i++;
		if (!prompt->cmd_line[i])
			break ;
		prompt->num_word++;
		while (prompt->cmd_line[i] \
		&& prompt->cmd_line[i] != ' ' \
		&& prompt->cmd_line[i] != '\n' \
		&& prompt->cmd_line[i] != '\t')
			i++;
	}
}

int	cmd_line_split(t_prompt *prompt)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	prompt->split_cmd_line = (char **)ft_calloc \
	(prompt->num_word + 1, sizeof(char *));
	if (!prompt->split_cmd_line)
		return (msg_err("malloc"), ERR);
	while (prompt->cmd_line[++i])
	{
		while (prompt->cmd_line[i] == ' ' \
		|| prompt->cmd_line[i] == '\t' \
		|| prompt->cmd_line[i] == '\n')
			i++;
		if (!prompt->cmd_line[i])
			break ;
		prompt->split_cmd_line[++j] = &prompt->cmd_line[i];
		while (prompt->cmd_line[i] \
		&& prompt->cmd_line[i] != ' ' \
		&& prompt->cmd_line[i] != '\t' \
		&& prompt->cmd_line[i] != '\n')
			i++;
		prompt->cmd_line[i] = '\0';
	}
	return (SUCCESS);
}

void	get_prompt(t_prompt *prompt)
{
	int	gnl;

	ft_memset(prompt, 0, sizeof(t_prompt));
	gnl = ft_get_next_line(STDIN_FILENO, &prompt->cmd_line);
	if (gnl < 0)
	{
		msg_err("ft_get_next_line");
		return ;
	}
	if (gnl == 0)
		exit_shell();
	count_words(prompt);
	if (cmd_line_split(prompt))
		return ;
}

// void	set_prompt(t_prompt *prompt)
// {
// 	int	i;

// 	i = -1;
// 	while (prompt->split_cmd_line[++i])
// 	{
		
// 	}
// }

void	exec_builtin(t_prompt *prompt, char **envp)
{
	if (!ft_strcmp(prompt->split_cmd_line[0], "echo"))
		echo(prompt->num_word, prompt->split_cmd_line);
	else if (!ft_strcmp(prompt->split_cmd_line[0], "pwd"))
		print_pwd();
	else if (!ft_strcmp(prompt->split_cmd_line[0], "cd"))
		cd(prompt->num_word, prompt->split_cmd_line, envp);
}

void	exec_cmd(t_data *data)
{
	exec_builtin(data->prompt, data->arg->e);
}

void	display_prompt(char *shell_name)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
}

int	main(int argc, char *argv[], char *env[])
{
	t_data		data;
	t_prompt	prompt;
	t_arg		arg;

	arg = (t_arg){argc, argv, env};
	data = (t_data){&arg, argv[0], &prompt};
	while (1)
	{
		display_prompt(data.shell_name);
		get_prompt(&prompt);
		// set_prompt(&prompt);
		exec_cmd(&data);
		free(prompt.split_cmd_line);
		free(prompt.cmd_line);
	}
}
