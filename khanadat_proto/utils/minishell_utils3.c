/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:07:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 15:00:43 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell_define.h"
#include "minishell_utils.h"
#include "minishell_err.h"
#include "libft.h"

static void	set_signaled(bool *signaled, int status, \
	int *exit_status);

void	catch_final_status(int status, t_mini *mini)
{
	int	exit_status;

	exit_status = 0;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) \
		== (unsigned char)SYSTEMCALL_EXITSTATUS)
			systemcall_minishell_exit(mini, NULL);
		exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		set_signaled(&mini->signaled, status, &exit_status);
	store_status(exit_status, mini);
}

static void	set_signaled(bool *signaled, int status, \
	int *exit_status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (!(*signaled) && sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (!(*signaled) && sig == SIGINT)
		ft_putchar_fd('\n', STDERR_FILENO);
	*exit_status = WTERMSIG(status) + 128;
	(*signaled) = true;
}

void	set_handler(t_mini *mini, int sig, void handler(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, (struct sigaction *)0))
		systemcall_minishell_exit(mini, "sigaction");
}

// void	quit_cmd(int sig)
// {
// 	received_sig = DEFAULT_SIG_NUM + sig;
// 	exit(sig + DEFAULT_SIG_NUM);
// }

// void	restart_prompt(int sig)
// {
// 	ft_putchar_fd('\n', STDERR_FILENO);
// 	received_sig = DEFAULT_SIG_NUM + sig;
// 	exit(DEFAULT_SIG_NUM + sig);
// }
