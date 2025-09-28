/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:16:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/27 18:17:00 by khanadat         ###   ########.fr       */
/*      char	*program_name(char *set)                                                                      */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"
#include "ast.h"
#include "tokenizer.h"

int	set_envp(t_mini *mini, char *envp[])
{
	size_t	i;

	while (envp[mini->envp_len])
		(mini->envp_len)++;
	mini->envp_size = (mini->envp_len) * 2;
	mini->envp = ft_calloc(mini->envp_size + 1, sizeof(char *));
	if (!mini->envp)
		return (err_system_call("malloc"), ERR);
	i = 0;
	while (i < mini->envp_len)
	{
		mini->envp[i] = ft_strdup(envp[i]);
		if (!mini->envp[i])
		{
			while (i--)
				free(mini->envp[i]);
			return (free(mini->envp), err_system_call("malloc"), ERR);
		}
		i++;
	}
	return (SUCCESS);
}

int	set_prompt(t_mini *mini)
{
	mini->prompt = ft_strjoin \
	(access_program_name(NULL), "$ ");
	if (!mini->prompt)
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}

int	set_minishell(t_mini *mini, char *envp[])
{
	ft_bzero(mini, sizeof(t_mini));
	if (set_envp(mini, envp))
		return (ERR);
	if (set_prompt(mini))
		return (ERR);
	return (SUCCESS);
}


int	set_handler(int sig, void handler(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, (struct sigaction *)0))
		return (err_system_call("sigaction"), ERR);
	return (SUCCESS);
}

void	quit_cmd(int sig)
{
	exit(sig + 128);
}

void	restart_prompt(int sig)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(128 + sig);
}

void	send_prompt(t_mini *mini, int *pfd)
{
	char	*child_line;
	size_t	line_len;

	close(pfd[0]);
	set_handler(SIGINT, restart_prompt);
	child_line = readline(mini->prompt);
	if (!child_line)
		exit((close(pfd[1]), NO_NEW_LINE));
	line_len = ft_strlen(child_line);
	if (write(pfd[1], &line_len, sizeof(size_t)) < 0)
		exit((close(pfd[1]), free(child_line), ERR));
	if (write(pfd[1], child_line, line_len) < 0)
		exit((close(pfd[1]), free(child_line), ERR));
	exit((close(pfd[1]), free(child_line), SUCCESS));
}

int	receive_prompt(t_mini *mini, int *pfd, pid_t prompt_id)
{
	int		prompt_status;
	size_t	line_len;

	waitpid(prompt_id, &prompt_status, 0);
	close(pfd[1]);
	if (WEXITSTATUS(prompt_status) == GOT_SIGNAL)
		return (close(pfd[0]), PROMPT_CONTINUE);
	if (WEXITSTATUS(prompt_status) == NO_NEW_LINE)
		noline_minishell_exit((close(pfd[0]), mini));
	if (WEXITSTATUS(prompt_status) == ERR)
		systemcall_minishell_exit((close(pfd[0]), mini), "write");
	if (read(pfd[0], &line_len, sizeof(size_t)) != sizeof(size_t))
		systemcall_minishell_exit((close(pfd[0]), mini), "read");
	mini->line = ft_calloc(line_len + 1, sizeof(char));
	if (!mini->line)
		systemcall_minishell_exit((close(pfd[0]), mini), "malloc");
	if (read(pfd[0], mini->line, line_len) != (ssize_t)line_len)
		systemcall_minishell_exit((close(pfd[0]), mini), "read");
	close(pfd[0]);
	if (!*(mini->line))
		return (safe_free((void **)&(mini->line)), PROMPT_CONTINUE);
	add_history(mini->line);
	return (SUCCESS);
}

// set node and free line
int	set_node(t_mini *mini)
{
	int		status;
	t_token	*token;

	status = get_token(&token, mini->line);
	if (status < 0)
		systemcall_minishell_exit(mini, NULL);
	if (status == SYNTAX_ERR)
		return (safe_free \
			((void **)&(mini->line)), \
			PROMPT_CONTINUE);
	status = get_node(&(mini->node), token);
	if (status < 0)
		systemcall_minishell_exit \
		((free_token(&token), mini), NULL);
	if (status == SYNTAX_ERR)
		return (free_token(&token), \
			safe_free((void **)&(mini->line)), \
			PROMPT_CONTINUE);
	return (free_token(&token), \
		safe_free((void **)&(mini->line)), \
		SUCCESS);
}

void	print_node(t_node *node)
{
	t_red	*r;
	t_word	*w;

	if (node->lhs)
		print_node(node->lhs);
	if (node->kind == ND_AND)
		printf("and\n");
	else if (node->kind == ND_OR)
		printf("or\n");
	else if (node->kind == ND_PIPE)
		printf("pipe\n");
	else if (node->kind == ND_CMD)
	{
		printf("cmd: ");
		w = node->word;
		while (w)
		{
			printf("%s ", w->word);
			w = w->next;
		}
		printf("\n");
		r = node->red;
		while (r)
		{
			if (r->kind == RD_APPEND)
				printf("append: ");
			else if (r->kind == RD_HEREDOC)
				printf("heredoc: ");
			else if (r->kind == RD_IN)
				printf("redirect in: ");
			else if (r->kind == RD_OUT)
				printf("redirect_out: ");
			printf("%s\n", r->file);
			r = r->next;
		}
	}
	if (node->rhs)
		print_node(node->rhs);
}

void	exec_prompt(t_mini *mini)
{
	print_node(mini->node);
}

void	minishell(t_mini *mini)
{
	pid_t	prompt_id;
	int		pfd[2];

	while (1)
	{
		set_handler(SIGINT, SIG_IGN);
		set_handler(SIGQUIT, SIG_IGN);
		if (pipe(pfd))
			systemcall_minishell_exit(mini, "pipe");
		prompt_id = fork();
		if (prompt_id < 0)
			systemcall_minishell_exit(mini, "fork");
		if (prompt_id == 0)
			send_prompt(mini, pfd);
		if (receive_prompt(mini, pfd, prompt_id) == PROMPT_CONTINUE)
			continue ;
		if (set_node(mini) == PROMPT_CONTINUE)
			continue ;
		exec_prompt(mini);
		free_node(&mini->node);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	if (argc != 1)
		return (err_invalid_arg(argv[1]), FAILURE);
	if (!access_program_name(argv[0]))
		return (FAILURE);
	if (set_minishell(&mini, envp))
		exit((free_program_name(), FAILURE));
	minishell(&mini);
	return (FAILURE);
}
