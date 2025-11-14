/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:46:03 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/19 11:56:59 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_err.h"
#include "minishell_set.h"
#include "prompt.h"
#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	mini;

	if (argc != 1)
		return (err_invalid_arg(argv[1]), FAILURE);
	if (set_minishell(&mini, envp))
		exit(FAILURE);
	minishell(&mini);
	return (FAILURE);
}
