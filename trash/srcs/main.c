/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:28:16 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/12 17:40:36 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "define.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define DEFAULT 0

#define END_STATUS 127
#define ERR_MALLOC 1

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
	ft_putendl_fd("Error: syntax error", STDERR_FILENO);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	skip_quotation(t_prompt *prompt, size_t *i)
{
	char	*tmp;

	if (prompt->cmd_line[*i] == '\'')
	{
		tmp = ft_strchr(&prompt->cmd_line[*i + 1], '\'');
		if (!tmp)
			return (msg_syntax_err(), ERR);
		*i += tmp - &prompt->cmd_line[*i] + 1;
		return (SUCCESS);
	}
	tmp = ft_strchr(&prompt->cmd_line[*i + 1], '\"');
	if (!tmp)
		return (msg_syntax_err(), ERR);
	*i += tmp - &prompt->cmd_line[*i] + 1;
	return (SUCCESS);
}

void	skip_words(const char *cmd_line, size_t *i)
{
	while (cmd_line[*i] \
	&& !ft_isspace(cmd_line[*i])
	&& cmd_line[*i] != '\''
	&& cmd_line[*i] != '\"')
		(*i)++;
}

// validation
int	validate_cmd_line(t_prompt *prompt)
{
	bool 	space;
	size_t	i;

	space = true;
	i = 0;
	while (prompt->cmd_line[i])
	{
		while (ft_isspace(prompt->cmd_line[i]))
			space = (i++, true);
		if (!prompt->cmd_line[i])
			break ;
		if (space)
			prompt->num_word++;
		space = false;
		if (prompt->cmd_line[i] == '\'' || prompt->cmd_line[i] == '\"')
		{
			if (skip_quotation(prompt, &i))
				return (ERR);
			continue;
		}
		skip_words(prompt->cmd_line, &i);
	}
	return (SUCCESS);
}

void	handle_words(t_prompt *prompt, size_t *i, size_t *j)
{
	if (prompt->cmd_line[*i] == '\'')
	{
		prompt->splited_cmd_line[(*j)++] = &prompt->cmd_line[++(*i)];
		*i += ft_strchr(&prompt->cmd_line[*i], '\'') - &prompt->cmd_line[*i];
	}
	else if (prompt->cmd_line[*i] == '\"')
	{
		prompt->splited_cmd_line[(*j)++] = &prompt->cmd_line[++(*i)];
		*i += ft_strchr(&prompt->cmd_line[*i], '\"') - &prompt->cmd_line[*i];
	}
	else
	{
		prompt->splited_cmd_line[(*j)++] = &prompt->cmd_line[(*i)];
		skip_words(prompt->cmd_line, i);
	}
	if (prompt->cmd_line[*i])
		prompt->cmd_line[(*i)++] = '\0';
}

void	cat_words(t_prompt *prompt, size_t *i, char	**split)
{
	size_t	len;

	len = 0;
	if (prompt->cmd_line[*i] == '\'')
	{
		(*i)++;
		len += ft_strchr(&prompt->cmd_line[*i], '\'') - &prompt->cmd_line[*i];
	}
	else if (prompt->cmd_line[*i] == '\"')
	{
		(*i)++;
		len += ft_strchr(&prompt->cmd_line[*i], '\"') - &prompt->cmd_line[*i];
	}
	else
		skip_words(prompt->cmd_line + *i, &len);
	ft_strlcat(*split, &prompt->cmd_line[*i], ft_strlen(*split) + len);
	*i += len + (prompt->cmd_line[*i] == '\'' || prompt->cmd_line[*i] == '\"');
}

void	set_splited_cmd_line(t_prompt *prompt)
{
	size_t	i;
	size_t	j;
	bool	space;

	i = 0;
	j = 0;
	space = true;
	while (prompt->cmd_line[i])
	{
		while (ft_isspace(prompt->cmd_line[i]))
			space = (i++, true);
		if (!prompt->cmd_line[i])
			break ;
		if (!space)
			space = (cat_words(prompt, &i, &prompt->splited_cmd_line[j - 1]), false);
		else
			handle_words(prompt, &i, &j);
	}
}

// t_promptの構造体を設定
int	set_prompt(t_prompt *prompt)
{
	if (validate_cmd_line(prompt))
		return (ERR);
	// fprintf(stderr, "%d\n", prompt->num_word);
	// prompt->word_cmdを数えることまではできた。
	// あとはちゃんとsplited_cmd_lineに格納する。

	prompt->splited_cmd_line = (char **)ft_calloc \
	(prompt->num_word + 1, sizeof(char *));
	if (!prompt->splited_cmd_line)
		return (msg_err("malloc failed"), ERR);
	set_splited_cmd_line(prompt);
	for (int i = 0; i < prompt->num_word; i++)
		fprintf(stderr, "%s\n", prompt->splited_cmd_line[i]);
	return (ERR);
	return (SUCCESS);
}

int	exec_builtin(t_prompt *prompt, t_data *data)
{
	if (!ft_strcmp(prompt->splited_cmd_line[0], "echo"))
		return (builtin_echo(prompt->num_word, prompt->splited_cmd_line));
	else if (!ft_strcmp(prompt->splited_cmd_line[0], "pwd"))
		return (print_pwd());
	else if (!ft_strcmp(prompt->splited_cmd_line[0], "cd"))
		return (builtin_cd(prompt->num_word, \
			prompt->splited_cmd_line, data->home_dir));
	return (1);
}

void	exec_cmd(t_data *data)
{
	if (!exec_builtin(data->prompt, data))
		return ;
}

void	display_prompt(t_data *data, t_prompt *prompt)
{
	ft_memset(prompt, 0, sizeof(t_prompt));
	prompt->cmd_line = readline(data->prompt_name);
	if (!prompt->cmd_line)
		exit((ft_putendl_fd("exit", STDOUT_FILENO), \
		free(data->prompt_name), \
		rl_clear_history(), 0));
	if (*prompt->cmd_line)
		add_history(prompt->cmd_line);
}

char	*get_home_dir(char *envp[])
{
	int		i;
	char	*home;

	i = -1;
	home = NULL;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "HOME=", 5))
			break ;
	if (envp[i])
		home = envp[i] + 5;
	return (home);
}

char	*get_prompt(char *argv)
{
	char	*prompt;

	prompt = ft_strjoin(ft_strchr(argv, '/') + 1, "$ ");
	if (!prompt)
		exit((msg_err("malloc failed"), ERR_MALLOC));
	return (prompt);
}

static void on_sigint(int signo) {
    (void)signo;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;
	t_prompt	prompt;
	t_arg		arg;

    signal(SIGINT,  on_sigint);
    signal(SIGQUIT, SIG_IGN);
	arg = (t_arg){argc, argv, envp};
	data = (t_data){.arg = &arg, .prompt_name = get_prompt(argv[0]), \
		.home_dir = get_home_dir(envp), .prompt = &prompt};
	while (1)
	{
		display_prompt(&data, &prompt);
		if (!set_prompt(&prompt))
			exec_cmd(&data);
		safe_free(prompt.splited_cmd_line);
		safe_free(prompt.cmd_line);
	}
}
