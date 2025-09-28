#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "status.h"
#include "minishell_err.h"
#include "ast.h"

// #define PATH_MAX 2048
#define GOT_SIGNAL 2
#define NO_LINE 1
#define CORE_DUMPED 3

typedef struct s_mini
{
	char	**envp;
	size_t	envp_size;
	size_t	envp_count;
	t_node	*node;
	char	*program_name;
	char	*prompt;
	char	**path_list;
}	t_mini;

void	quit_cmd(int sig)
{
	exit(sig + 128);
}

void	restart_prompt(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	exit(sig);
}

int	set_handler(int sig, void handler(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask))
		return (ERR);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, (struct sigaction *)0))
		return (ERR);
	return (0);
}

int	get_current_dir_path(t_mini *mini)
{
	mini->path_list = ft_calloc(2, sizeof(char *));
	if (!mini->path_list)
	// need fix as giving correct err msg.
		return (err_system_call("malloc"), ERR);
	*(mini->path_list) = ft_strdup(".");
	if (!*(mini->path_list))
		return (err_system_call("malloc"), \
		free(mini->path_list), ERR);
	return (SUCCESS);
}

#define PATH_LIST_LEN 10

int	store_path_list(t_mini *mini, char *envp[])
{
	mini->path_list \
	= ft_calloc(PATH_LIST_LEN + 1, sizeof(char *));
}

int	get_path_list(t_mini *mini, char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (get_current_dir_path(mini));
	return (store_path_list(mini, envp));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_mini		mini;
	char		*prompt;
	if (argc != 1)
		exit(1);

	// パスの候補を二重ポインタに動的に確保する。
	// path_list[0] = "/home/khanadat/bin\0"
	// path_list[1] = "/usr/local/sbin\0"
	// ...
	int	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5))
		{
			i++;
			continue ;
		}
		break ;
	}
	char	**path_list;
	if (!envp[i]) {
		path_list = ft_calloc(2, sizeof(char *));
		*path_list = ft_strdup(".");
	}
	else {
		size_t	path_list_len = 0;
		char	*path_start = ft_strchr(envp[i], '=') + 1;
		char	*path_end;
		while ((path_end = ft_strchr(path_start, ':')) != NULL)
		{
			path_list_len++;
			path_start = path_end + 1;
		}
		path_list = ft_calloc (path_list_len + 1, sizeof(char *));
		path_start = ft_strchr(envp[i], '=') + 1;
		int	i = 0;
		while ((path_end = ft_strchr(path_start, ':')) != NULL)
		{
			if (*path_start == ':')
			{
				path_list[i++] = ft_strdup(".");
				while (*path_start == ':')
					path_start++;
				continue ;
			}
			path_list[i++] = ft_strndup(path_start, path_end - path_start);
			path_start = path_end + 1;
		}
	}

	// 実行ファイル名を取得
	char	*program_name;
	program_name = ft_strchr(argv[0], '/');
	if (!program_name)
		program_name = argv[0];
	else
	{
		char	*before;
		before = program_name;
		while (1)
		{
			program_name = ft_strchr(before + 1, '/');
			if (!program_name)
				break ;
			before = program_name;
		}
		program_name = before + 1;
	}
	size_t	program_name_len = ft_strlen(program_name);
	prompt = ft_calloc(program_name_len + 3, sizeof(char));
	ft_memmove(prompt, program_name, program_name_len);
	ft_memmove(prompt + program_name_len, "$ ", 2);

	// 固定長確保したスタックにパス情報を保存していく
	char	path[PATH_MAX];
	// 全体の無限ループ
	while (1)
	{
		// 親プロセスはシグナルctrl + cを無視
		set_handler(SIGINT, SIG_IGN);
		set_handler(SIGQUIT, SIG_IGN);

		// 親プロセスに取得したプロンプトを書き込むためにパイプ
		int		pfd[2];
		if (pipe(pfd) < 0)
			exit((perror("pipe"), free(prompt), \
			free_split(path_list), ERR));

		pid_t	prompt_id;
		prompt_id = fork();
		if (prompt_id < 0)
			exit((perror("fork"), free(prompt), \
			free_split(path_list), ERR));

		// 子プロセス内でプロンプトを取得してそれを親プロセスに書き込み。
		if (prompt_id == 0)
		{
			char	*child_line;
			close(pfd[0]);
			set_handler(SIGINT, restart_prompt);
			child_line = readline(prompt);
			if (!child_line)
				exit((close(pfd[1]), NO_LINE));
			size_t	line_len = ft_strlen(child_line);
			if (write(pfd[1], &line_len, sizeof(size_t)) == sizeof(size_t)
			&& write(pfd[1], child_line, line_len) == (ssize_t)line_len)
				exit((close(pfd[1]), free(child_line), 0));
			else
				exit((close(pfd[1]), free(child_line), \
				perror("write"), ERR));
		}

		// 子プロセスから取得したexit statusを確認して、
		// 親プロセス上で行うパターンに応じて場合分け。
		int	prompt_status;
		waitpid(prompt_id, &prompt_status, 0);
		close(pfd[1]);
		if (WEXITSTATUS(prompt_status) == GOT_SIGNAL)
		{
			close(pfd[0]);
			continue ;
		}
		if (WEXITSTATUS(prompt_status) == NO_LINE)
			exit((rl_clear_history(), free(prompt), \
			free_split(path_list), close(pfd[0]), 0)) ;
		if (WEXITSTATUS(prompt_status) == ERR)
			exit((rl_clear_history(), free(prompt), \
			free_split(path_list), close(pfd[0]), ERR));

		// 子プロセスがパイプに書き込んだものを読み取り。
		char	*line = NULL;
		size_t	len;
		if (read(pfd[0], &len, sizeof(size_t)) != sizeof(size_t))
			exit((rl_clear_history(), free(prompt), \
			free_split(path_list), perror("read"), close(pfd[0]), ERR));
		line = ft_calloc(len + 1, sizeof(char));
		if (read(pfd[0], line, len) != (ssize_t)len)
			exit((rl_clear_history(), free(prompt), \
			free_split(path_list), perror("read"), free(line), close(pfd[0]), ERR));
		close(pfd[0]);

		// 何も入力がなくリターンがあったとき
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		int	j = -1;
		char	**line_argv = ft_split(line, ' ');
		free(line);

		// 空白のみの入力のとき
		if (!*line_argv)
		{
			free_split(line_argv);
			continue ;
		}

		// 入力されたコマンドのパスを取得
		size_t	line_argv_len = ft_strlen(line_argv[0]);
		// 入力されたコマンドが相対パスのとき
		if (access(line_argv[0], F_OK)) {
			while (path_list[++j])
			{
				ft_memset(path, 0, PATH_MAX);
				ft_memmove(path, path_list[j], ft_strlen(path_list[j]));
				ft_memmove(path + ft_strlen(path_list[j]), "/", 1);
				ft_memmove(path + ft_strlen(path_list[j]) + 1, line_argv[0], line_argv_len);
				if (!access(path, F_OK))
					break ;
			}
			if (!path_list[j]) {
				fprintf(stderr, "%s: %s: command not found\n", program_name, line_argv[0]);
				free_split(line_argv);
				continue ;
			}
		}
		// 絶対パスのとき
		else {
			memset(path, 0, PATH_MAX);
			ft_memmove(path, line_argv[0], line_argv_len);
		}
		if (access(path, X_OK)) {
			fprintf(stderr, "%s: %s: permission denied\n", program_name, line_argv[0]);
			free_split(line_argv);
			continue ;
		}

		// 実行部分, オペレーションは未実装
		pid_t	id = fork();
		if (id == 0)
		{
			set_handler(SIGINT, quit_cmd);
			set_handler(SIGQUIT, SIG_DFL);
			execve(path, line_argv, envp);
		}
		else
		{
			int	status;
			waitpid(id , &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == CORE_DUMPED)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
		free_split(line_argv);
	}
	rl_clear_history();
	free(prompt);
	free_split(path_list);
	return (0);
}
