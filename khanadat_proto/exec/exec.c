/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/08 01:26:15 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "minishell_err.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "status.h"
#include "libft.h"
#include "expand.h"
#include "get_path.h"
#include "ast.h"
#include "set_redirect.h"
#include "builtin.h"

size_t	count_word(t_word *head)
{
	size_t	len;

	len = 0;
	while (head)
		head = (len++, head->next);
	return (len);
}

int	store_argv(t_word *head, char ***argv)
{
	size_t	i;

	*argv = ft_calloc \
	(count_word(head) + 1, sizeof(char *));
	if (!*argv)
		return (ERR);
	i = 0;
	while (head)
	{
		(*argv)[i++] = head->word;
		head = head->next ;
	}
	return (SUCCESS);
}

int	set_abs_path(char **dir)
{
	size_t	i;
	size_t	dir_len;
	size_t	pwd_len;
	char	*abs_path;
	char	*pwd;

	if (**dir == '/')
	{
		*dir = ft_strdup(*dir);
		if (!*dir)
			return (ERR);
		return (SUCCESS);
	}
	dir_len	= ft_strlen(*dir);
	pwd = mini_getcwd();
	pwd_len = ft_strlen(pwd);
	abs_path = ft_calloc(dir_len + pwd_len + 2, sizeof(char));
	if (!abs_path)
		return (ERR);
	i = 0;
	ft_memmove(abs_path + i, pwd, pwd_len);
	i += pwd_len;
	ft_memmove(abs_path + i, "/", 1);
	i += 1;
	ft_memmove(abs_path + i, *dir, dir_len);
	*dir = abs_path;
	return (SUCCESS);
}

void    exec_child_proc(t_mini *mini, char **argv)
{
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	get_path(&path, mini, argv);
	execve(path, argv, mini->envp);
	systemcall_minishell_exit(mini, "execve");
}

#define IS_FIRST 1
#define IS_MIDDLE 2
#define IS_LAST 3

void	set_rfd(t_mini *mini, t_cmd *cmd)
{
	if (cmd->rfd[0] != FD_DFL)
	{
		cmd->saved[0] = dup(STDIN_FILENO);
		if (cmd->rfd[0] != STDOUT_FILENO)
		{
			close(STDIN_FILENO);
			if (dup2(cmd->rfd[0], STDIN_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
		}
	}
	if (cmd->rfd[1] != FD_DFL)
	{
		cmd->saved[1] = dup(STDOUT_FILENO);
		if (cmd->rfd[1] != STDIN_FILENO)
		{
			close(STDOUT_FILENO);
			if (dup2(cmd->rfd[1], STDOUT_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
		}
	}
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	if (set_redirect(mini, node->red, node->cmd))
		return ;
	set_rfd(mini, node->cmd);
	if (exec_builtin(mini, node->cmd))
		return ;
	else
		exec_child_proc(mini, node->cmd->argv);
}

void	wait_pipe(t_mini *mini, t_node *node)
{
	int	status;

	if (node->cmd->pid != PID_BUILTIN)
	{
		if (waitpid(node->cmd->pid, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		store_status(status, mini);
		catch_signal(status, mini);
	}
	if (node->cmd->rfd[0] != FD_DFL)
	{
		close(node->cmd->rfd[0]);
		if (dup2(node->cmd->saved[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(node->cmd->saved[0]);
	}
	if (node->cmd->rfd[1] != FD_DFL)
	{
		close(node->cmd->rfd[1]);
		if (dup2(node->cmd->saved[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(node->cmd->saved[1]);
	}
}

void	exec_pipe_cmd(t_mini *mini, t_node *node)
{
	int		pp[2];
	pid_t	ret;

	if (node->kind == ND_CMD)
	{
		exec_cmd(mini, node);
		normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
	}
	else
	{
		pipe(pp);
		ret = fork();
		if (ret < 0)
			systemcall_minishell_exit(mini, "fork");
		if (ret == 0)
		{
			close(pp[0]);
			if (dup2(pp[1], STDOUT_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
			close(pp[1]);
			exec_pipe_cmd(mini, node->lhs);
		}
		else
		{
			close(pp[1]);
			if (dup2(pp[0], STDIN_FILENO) < 0)
				systemcall_minishell_exit(mini, "dup2");
			close(pp[0]);
			if (mini->signaled)
				normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
			exec_cmd(mini, node->rhs);
			normal_minishell_exit(mini, NULL, NULL, ft_atoi(mini->status));
		}
	}
}

void	expand_pipe_group(t_mini *mini, t_node *node)
{
	if (!node)
		return ;
	expand_pipe_group(mini, node->lhs);
	if (node->kind == ND_CMD)
	{
		if (expand_node(node, mini))
		{
			node->expand_err = true;
			return ;
		}
		if (store_argv(node->word, &node->cmd->argv))
			systemcall_minishell_exit(mini, "malloc");
		if (!mini->signaled && write_heredoc(mini, node->red, node->cmd))
		{
			mini->signaled = true;
			return ;
		}
	}
	expand_pipe_group(mini, node->rhs);
}

void	exec_node(t_mini *mini, t_node *node)
{
	expand_pipe_group(mini, node);
	if (node->kind == ND_PIPE)
	{
		mini->is_pipe = true;
		node->rhs->cmd->pid = fork();
		if (node->rhs->cmd->pid == 0)
			exec_pipe_cmd(mini, node);
		else
			wait_pipe(mini, node->rhs);
		mini->is_pipe = false;
	}
	if (node->kind == ND_CMD)
	{
		if (node->expand_err)
			return ;
		if (set_redirect(mini, node->red, node->cmd))
			return ;
		set_rfd(mini, node->cmd);
		if (exec_builtin(mini, node->cmd))
		{
			wait_pipe(mini, node);
			return ;
		}
		node->cmd->pid = fork();
		if (node->cmd->pid < 0)
			systemcall_minishell_exit(mini, "fork");
		if (node->cmd->pid == 0)
			exec_child_proc(mini, node->cmd->argv);
		else
			wait_pipe(mini, node);
	}
	mini->signaled = false;
}

void	exec_prompt(t_mini *mini, t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_OR)
	{
		exec_prompt(mini, node->lhs);
		if (!ft_strcmp("0", mini->status))
			return ;
		exec_prompt(mini, node->rhs);
	}
	else if (node->kind == ND_AND)
	{
		exec_prompt(mini, node->lhs);
		if (ft_strcmp("0", mini->status))
			return ;
		exec_prompt(mini, node->rhs);
	}
	else
		exec_node(mini, node);
}
