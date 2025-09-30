/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lib3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:07:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/29 17:12:39 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "status.h"
#include "minishell_define.h"
#include "minishell_err.h"
#include "libft.h"

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
	exit(sig + DEFAULT_SIG_NUM);
}

void	restart_prompt(int sig)
{
	ft_putchar_fd('\n', STDERR_FILENO);
	received_sig = DEFAULT_SIG_NUM + sig;
	exit(DEFAULT_SIG_NUM + sig);
}
