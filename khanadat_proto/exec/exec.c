/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:15:28 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/04 23:14:33 by khanadat         ###   ########.fr       */
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

void	close_cfd(int *cfd)
{
	if (cfd[0] != STDIN_FILENO)
		close(cfd[0]);
	if (cfd[1] != STDOUT_FILENO)
		close(cfd[1]);
}

#define CWD_INIT_SIZE 4096

char	*mini_getcwd(void)
{
	char	*cwd;
	size_t	cwd_size;

	cwd_size = CWD_INIT_SIZE;
	cwd = malloc(sizeof(char) * cwd_size);
	while (cwd && !getcwd(cwd, cwd_size))
	{
		free(cwd);
		cwd_size *= 2;
		cwd = malloc(sizeof(char) * cwd_size);
	}
	return (cwd);
}

void	exec_pwd(t_mini *mini, char **argv)
{
	char	*cwd;

	cwd = mini_getcwd();
	if (!cwd)
	{
		free(argv);
		systemcall_minishell_exit(mini, "malloc");
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	store_status(0, mini);
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

int	set_mini_envp(char *var, char *val, char **envp_i)
{
	size_t	len;
	size_t	i;
	size_t	var_len;
	size_t	val_len;

	if (*envp_i)
		free(*envp_i);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	len = var_len + 1 + val_len;
	*envp_i = ft_calloc(len + 1, sizeof(char));
	if (!*envp_i)
		return (ERR);
	i = 0;
	ft_memmove(*envp_i, var, var_len);
	i += var_len;
	ft_memmove(*envp_i + i, "=", 1);
	i += 1;
	ft_memmove(*envp_i + i, val, val_len);
	return (SUCCESS);
}

int	add_mini_len(t_mini *mini)
{
	char	**tmp;

	mini->envp_len++;
	if (mini->envp_len > mini->envp_size)
	{
		mini->envp_size *= 2;
		tmp = ft_calloc(mini->envp_size + 1, sizeof(char *));
		if (!tmp)
			return (err_system_call("malloc"), ERR);
		ft_memmove(tmp, mini->envp, mini->envp_size / 2 * sizeof(char *));
		free(mini->envp);
		mini->envp = tmp;
	}
	return (SUCCESS);
}

int	mini_export(char *var, char *val, t_mini *mini)
{
	size_t	var_len;
	size_t	i;

	i = 0;
	var_len = ft_strlen(var);
	while (mini->envp[i])
	{
		if (!ft_strncmp(var, mini->envp[i], var_len) \
		&& mini->envp[i][var_len] == '=')
			break ;
		i++;
	}
	if (!mini->envp[i] && add_mini_len(mini))
		return (err_system_call("malloc"), ERR);
	if (set_mini_envp(var, val, &mini->envp[i]))
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}

void	exec_cd(t_mini *mini, char **argv)
{
	char	*dir;

	if (!argv[1])
		dir = normal_getenv("HOME", mini);
	else
		dir = argv[1];
	if (!dir)
	{
		err_no_home("cd");
		return ;
	}
	if (argv[1] && argv[2])
	{
		err_too_many("cd");
		store_status(1, mini);
	}
	if (access(dir, F_OK))
	{
		err_cd(argv[1]);
		store_status(1, mini);
		return ;
	}
	if (!mini_is_dir(dir))
	{
		err_not_dir(argv[1]);
		store_status(1, mini);
		return ;
	}
	if (access(dir, X_OK))
	{
		err_cd_permission(argv[1]);
		store_status(1, mini);
		return ;
	}
	// if (set_abs_path(&dir))
	// {
	// 	free(argv);
	// 	systemcall_minishell_exit(mini, "malloc");
	// }
	if (chdir(dir))
		perror("chdir");
	// free(dir);
	dir = mini_getcwd();
	if (mini_export("PWD", dir, mini))
		normal_minishell_exit(mini, &free, \
			argv, SYSTEMCALL_EXITSTATUS);
	free(dir);
	store_status(FAILURE, mini);
}

void	exec_env(t_mini *mini, char **argv)
{
	size_t	i;

	if (argv[1])
	{
		err_msg_env(argv[1]);
		store_status(FAILURE, mini);
		return ;
	}
	i = 0;
	while (i < mini->envp_len)
		ft_putendl_fd(mini->envp[i++], STDOUT_FILENO);
	store_status(SUCCESS, mini);
}

int	export_arg(t_mini *mini, char *arg, size_t var_len)
{
	size_t	i;

	i = 0;
	while (mini->envp[i])
	{
		if (!ft_strncmp(arg, mini->envp[i], var_len) \
			&& mini->envp[i][var_len] == '=')
			break ;
		i++;
	}
	if (mini->envp[i])
		free(mini->envp[i]);
	else if (!mini->envp[i] && add_mini_len(mini))
		return (err_system_call("malloc"), ERR);
	mini->envp[i] = ft_strdup(arg);
	if (!mini->envp[i])
		return (err_system_call("malloc"), ERR);
	return (SUCCESS);
}

void	exec_export(t_mini *mini, char **argv)
{
	size_t	i;
	size_t	var_len;
	char	*eq_ptr;

	if (!argv[1])
		exec_env(mini, argv);
	i = 0;
	while (argv[++i])
	{
		eq_ptr = ft_strchr(argv[i], '=');
		if (!eq_ptr)
			continue ;
		var_len = (size_t)(eq_ptr - argv[i]);
		if (!var_len || (var_len == 1 && *argv[i] == '$'))
		{
			err_export(argv[i]);
			store_status(FAILURE, mini);
			return ;
		}
		if (export_arg(mini, argv[i], var_len))
			normal_minishell_exit(mini, &free, \
				argv, SYSTEMCALL_EXITSTATUS);
	}
	store_status(SUCCESS, mini);
}

#define NEW_LINE_OPTION "-n"
#define NEW_LINE_OPTION_LEN 2

bool	new_line_checkr(char *arg)
{
	if (!*arg)
		return (true);
	if (*arg++ != '-')
		return (true);
	if (*arg != 'n')
		return (true);
	while (*arg && *arg == 'n')
		arg++;
	if (!*arg)
		return (false);
	return (true);
}

void	exec_echo(t_mini *mini, char **argv)
{
	size_t	i;
	bool	print_new_line;

	print_new_line = new_line_checkr(argv[1]);
	i = !print_new_line;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	store_status(SUCCESS, mini);
}

bool	exec_builtin(t_mini *mini, char **argv)
{
	if (!ft_strcmp(argv[0], "pwd"))
		return (exec_pwd(mini, argv), true);
	if (!ft_strcmp(argv[0], "cd"))
		return (exec_cd(mini, argv), true);
	if (!ft_strcmp(argv[0], "env"))
		return (exec_env(mini, argv), true);
	if (!ft_strcmp(argv[0], "export"))
		return (exec_export(mini, argv), true);
	if (!ft_strcmp(argv[0], "echo"))
		return (exec_echo(mini, argv), true);
	// if (!ft_strcmp(argv[0], "unset"))
	// 	return (true);
	// if (!ft_strcmp(argv[0], "exit"))
	// 	return (true);
	return (false);
}

void    exec_child_proc(t_mini *mini, char **argv)
{
	char	*path;

	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
	get_path(&path, mini, argv);
	execve(path, argv, mini->envp);
	exit(0);
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	pid_t	cmd_id;
	int		status;
	char	**argv;
	int	 	cfd[2];
	int		saved[2];

	if (expand_node(node, mini))
		return ;
	if (store_argv(node->word, &argv))
		systemcall_minishell_exit(mini, "malloc");
	cfd[0] = STDIN_FILENO;
	cfd[1] = STDOUT_FILENO;
	if (set_redirect(mini, node->red, cfd))
	{
		close_cfd(cfd);
		return ;
	}
	if (cfd[0] != STDIN_FILENO)
	{
		saved[0] = dup(STDIN_FILENO);
		if (saved[0] < 0)
			systemcall_minishell_exit(mini, "dup");
		dup2(cfd[0], STDIN_FILENO);
	}
	if (cfd[1] != STDOUT_FILENO)
	{
		saved[1] = dup(STDOUT_FILENO);
		if (saved[1] < 0)
			systemcall_minishell_exit(mini, "dup");
		dup2(cfd[1], STDOUT_FILENO);
	}
	if (!exec_builtin(mini, argv))
	{
		cmd_id = fork();
		if (cmd_id < 0)
			systemcall_minishell_exit(mini, "fork");
		if (cmd_id == 0)
			exec_child_proc(mini, argv);
		if (waitpid(cmd_id, &status, 0) < 0)
			systemcall_minishell_exit(mini, "waitpid");
		catch_signal(status, mini);
	}
	if (cfd[0] != STDIN_FILENO)
	{
		close(cfd[0]);
		if (dup2(saved[0], STDIN_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(saved[0]);
	}
	if (cfd[1] != STDOUT_FILENO)
	{
		close(cfd[1]);
		if (dup2(saved[1], STDOUT_FILENO) < 0)
			systemcall_minishell_exit(mini, "dup2");
		close(saved[1]);
	}
	free(argv);
	if (mini->heredoc_name)
	{
		unlink(mini->heredoc_name);
		mini->heredoc_name = NULL;
	}
}

void	exec_prompt(t_mini *mini, t_node *node/* , t_NodeKind nkind */)
{
	if (!node)
		return ;
	if (node->lhs)
		exec_prompt(mini, node->lhs/* , node->kind */);
	if (node->kind == ND_CMD)
		exec_cmd(mini, node);
}
