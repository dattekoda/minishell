/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:33:24 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/22 08:51:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tokenizer.h"
#include "ast.h"
#include "libft.h"
#include "minishell_err.h"
#include "status.h"
#include "minishell_lib.h"

#define MINISHELL_PS1 "PS1=minishell$ "

char	*mini_getenv(char *var, t_mini *mini);

void	print_node(t_node *node)
{
	char	**v;
	t_red	*r;

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
		v = node->argv;
		while (*v)
			printf("%s ", *(v++));
		printf("\n");
		r = node->red;
		while (r)
		{
			if (r->kind == ND_APPEND)
				printf("append: ");
			else if (r->kind == ND_HEREDOC)
				printf("heredoc: ");
			else if (r->kind == ND_RED_IN)
				printf("redirect in: ");
			else if (r->kind == ND_RED_OUT)
				printf("redirect_out: ");
			printf("%s\n", r->file);
			r = r->next;
		}
	}
	if (node->rhs)
		print_node(node->rhs);
}

void	set_token_node(t_mini *mini, char *line)
{
	int		status;
	t_token	*token;

	token = NULL;
	mini->node = NULL;
	status = get_token(&token, line);
	if (status < 0)
		safe_minishell_exit(mini);
	if (status == SYNTAX_ERR)
		return ;
	status = get_node(&mini->node, token);
	free_token(token);
	free(line);
	line = NULL;
	if (status < 0)
		safe_minishell_exit(mini);
	if (status == SYNTAX_ERR)
		return ;
	print_node(mini->node);
	// invoke_cmds(mini);
	free_node(mini->node);
}

void	prompt(t_mini *mini)
{
	char	*prompt_name;
	char	*line;

	line = NULL;
	prompt_name = mini_getenv("PS1", mini);
	if (prompt_name)
		line = readline(prompt_name);
	else
		line = readline("");
	// set exit
	if (!line)
		return ;
	add_history(line);
	set_token_node(mini, line);
}

int	set_env(t_mini *mini, char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	mini->envp_size = count * 2;
	mini->envp = ft_calloc(mini->envp_size + 1, sizeof(char **));
	if (!mini->envp)
		return (ERR);
	while (envp[mini->envp_count])
	{
		mini->envp[mini->envp_count] = ft_strdup(envp[mini->envp_count]);
		if (!mini->envp[mini->envp_count])
			return (free_minienvp(mini), ERR);
		(mini->envp_count)++;
	}
	return (SUCCESS);
}

int	set_mini(t_mini **mini, char **envp)
{
	*mini = ft_calloc(1, sizeof(t_mini));
	if (!*mini)
		return (err_system_call("malloc"), ERR);
	if (set_env(*mini, envp))
		return (err_system_call("malloc"), \
		free(*mini), ERR);
	return (SUCCESS);
}

int	set_shell_name(t_mini *mini, char *argvzero)
{
	char	*shell_name;

	shell_name = ft_strchr(argvzero, '/');
	if (shell_name)
	{
		mini->envp[(mini->envp_count)] = ft_strjoin("PS1=", shell_name + 1);
		if (!mini->envp[(mini->envp_count)])
			return (ERR);
		if (safe_join(&mini->envp[(mini->envp_count)], "$ "))
			return (ERR);
	}
	else
	{
		mini->envp[(mini->envp_count)] \
		= ft_strdup(MINISHELL_PS1);
	}
	if (!mini->envp[mini->envp_count])
		return (ERR);
	mini->envp_count += 1;
	return (SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini	*mini;

	if (argc != 1)
		return (ft_putendl_fd("invalid number of arguments", STDERR_FILENO), \
		SYSTEMCALL_EXITSTATUS);
	if (set_mini(&mini, envp))
		exit(SYSTEMCALL_EXITSTATUS);
	if (set_shell_name(mini, argv[0]))
		return (free_minienvp(mini), SYSTEMCALL_EXITSTATUS);
	while (1)
		prompt(mini);
	exit(UNREACHABLE);
}
