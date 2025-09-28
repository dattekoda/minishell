#include <aio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "ast.h"
#include "status.h"
#include "libft.h"

typedef struct s_cmd
{
	t_node	*node;
	int		in_fd;
	int		out_fd;
	char	*heredoc_name;
}	t_cmd;

#define HEREDOC_FILE "/tmp/.heredoc"
#define HEREDOC_NAME_SIZE_MAX 10

bool	check_if_builin(char **argv)
{
	if (!ft_strcmp(argv[0], "cd")
	|| !ft_strcmp(argv[0], "echo")
	|| !ft_strcmp(argv[0], "env")
	|| !ft_strcmp(argv[0], "exit")
	|| !ft_strcmp(argv[0], "export")
	|| !ft_strcmp(argv[0], "unset")
	|| !ft_strcmp(argv[0], "pwd"))
		return (true);
	return (false);
}

void	exec_builtin(t_mini *mini, t_node *node)
{
	if (!ft_strcmp(node->argv[0], "cd"))
		exec_cd(mini, node);
	else if (!ft_strcmp(node->argv[0], "echo"))
		exec_echo(mini, node);
	else if (!ft_strcmp(node->argv[0], "env"))
		exec_env(mini, node);
	else if (!ft_strcmp(node->argv[0], "exit"))
		exec_env(mini, node);
	else if (!ft_strcmp(node->argv[0], "export"))
		exec_env(mini, node);
	else if (!ft_strcmp(node->argv[0], "unset"))
		exec_env(mini, node);
	else if (!ft_strcmp(node->argv[0], "pwd"))
		exec_env(mini, node);
}

// set tmp file's name
int	set_heredoc_name(t_cmd *cmd)
{
	static unsigned int	name = 0;
	char		*buffer[HEREDOC_NAME_SIZE_MAX + 1];
	int			tmp;
	int			i;

	buffer[HEREDOC_NAME_SIZE_MAX] = '\0';
	if (cmd->heredoc_name)
		free(cmd->heredoc_name);
	cmd->heredoc_name = NULL;
	tmp = name;
	i = HEREDOC_NAME_SIZE_MAX;
	if (tmp == 0)
		buffer[--i] = '0';
	while (tmp)
	{
		buffer[--i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	cmd->heredoc_name = ft_strjoin(HEREDOC_FILE, &buffer[i]);
	if (!cmd->heredoc_name)
		return (err_system_call("malloc"), ERR);
	name++;
	if (!access(cmd->heredoc_name, F_OK))
		return (set_heredoc_name(cmd));
	return (SUCCESS);
}

// if err return ERR, -1 ,or SUCCESS
int	set_heredoc(t_cmd *cmd, t_red *red)
{
	if (!cmd->in_fd && close(cmd->in_fd))
		return (err_system_call("close"), ERR);
	if (cmd->heredoc_name && unlink(cmd->heredoc_name))
		return (err_system_call("unlink"), ERR);
	if (set_heredoc_name(cmd))
		return (ERR);
	cmd->in_fd = open(cmd->heredoc_name, O_CREAT);
	if (cmd->in_fd < 0)
		return (err_system_call("open"), ERR);
	while ()
}

int	set_fd(t_cmd *cmd, t_red *red)
{
	int	status;

	while (red)
	{
		if (red->kind == RD_HEREDOC)
			status = set_heredoc(cmd, red);
		else if (red->kind == RD_APPEND)
			status = set_append(cmd, red);
		else if (red->kind == RD_IN)
			status = set_append(cmd, red);
		else if (red->kind == RD_OUT)
			status = set_append(cmd, red);
		red = red->next;
	}
	if (red->kind == RD_HEREDOC)
}

int	set_cmd(t_cmd **cmd, t_node *node)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
		return (err_system_call("malloc"), ERR);
	(*cmd)->node = node;
	if (set_fd(*cmd, node))
		return (ERR);
	return (SUCCESS);
}

void	exec_cmd(t_mini *mini, t_node *node)
{
	t_cmd	*cmd;

	if (set_cmd(&cmd, node))
		safe_minishell_exit(mini);
}

void	consume_node(t_mini *mini, t_node *node)
{
	pid_t	id;

	if (mini->node->lhs)
		consume_node(mini, mini->node->lhs);
	if (node->kind == ND_CMD)
		exec_cmd(mini, node);
	{
		set_fd(mini, node);
		if (check_if_builtin(node->argv))
			exec_builtin(mini, node);
		id = fork();
		if (id < 0)
			safe_minishell_exit(mini);
		if (id == 0)
		{
		}
	}
	// else if (node->kind == ND_PIPE)
	// else if (node->kind == ND_OR)
	// else if (node->kind == ND_AND)
}

void	invoke_cmds(t_mini *mini)
{
}
