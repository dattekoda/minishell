/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:16:59 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/12 15:17:54 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_set.h"
#include "libft.h"
#include "ast.h"
#include "tokenizer.h"
#include "exec.h"

void	send_prompt(t_mini *mini, int *pfd)
{
	char	*child_line;
	size_t	line_len;

	close(pfd[0]);
	set_handler(SIGINT, SIG_DFL);
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
	if (WIFSIGNALED(prompt_status))
		return (store_status(WTERMSIG(prompt_status) + 128, mini), \
		close(pfd[0]), ft_putchar_fd('\n', STDERR_FILENO), PROMPT_CONTINUE);
	if (WEXITSTATUS(prompt_status) == NO_NEW_LINE)
		minishell_exit((close(pfd[0]), mini));
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
		return (mini_safe_free((void **)&(mini->line)), PROMPT_CONTINUE);
	add_history(mini->line);
	return (SUCCESS);
}

// err_sig_msg(mini);
void	minishell(t_mini *mini)
{
	pid_t	prompt_id;
	int		pfd[2];

	while (1)
	{
		mini_safe_free((void **)&(mini->line));
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
		exec_prompt(mini, mini->node);
		free_node(&mini->node);
	}
}
