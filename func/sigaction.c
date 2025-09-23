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
// void	do_nothin(int sig)
// {
// }

// #define PATH_MAX 2048

void	quit_cmd(int sig)
{
	exit(sig + 128);
}

void	restart_prompt(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	exit(sig);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;
	if (argc != 1)
		exit(1);

	int	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5))
		{
			i++;
			continue ;
		}
		break ;
	}
	char	**path_list;
	if (!envp[i]) {
		path_list = calloc(2, sizeof(char *));
		*path_list = strdup(".");
	}
	else {
		size_t	path_list_len = 0;
		char	*path_start = strchr(envp[i], '=') + 1;
		char	*path_end;
		while ((path_end = strchr(path_start, ':')) != NULL)
		{
			path_list_len++;
			path_start = path_end + 1;
		}
		path_list = calloc (path_list_len + 1, sizeof(char *));
		path_start = strchr(envp[i], '=') + 1;
		int	i = 0;
		while ((path_end = strchr(path_start, ':')) != NULL)
		{
			if (*path_start == ':')
			{
				path_list[i++] = strdup(".");
				while (*path_start == ':')
					path_start++;
				continue ;
			}
			path_list[i++] = strndup(path_start, path_end - path_start);
			path_start = path_end + 1;
		}
	}

	char	*program_name;
	program_name = strchr(argv[0], '/') + 1;
	if (!program_name)
		exit(3);
	size_t	program_name_len = strlen(program_name);
	prompt = calloc(program_name_len + 3, sizeof(char));
	memmove(prompt, program_name, program_name_len);
	memmove(prompt + program_name_len, "$ ", 2);

	char	path[PATH_MAX];

	while (1)
	{
		struct sigaction	sa;

		sigemptyset(&sa.sa_mask);
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, (struct sigaction *) 0);
		int		pfd[2];
		if (pipe(pfd) < 0)
			exit((perror("pipe"), 42));

		pid_t	prompt_id;
		prompt_id = fork();
		if (prompt_id < 0)
			exit((perror("fork"), 42));
		if (prompt_id == 0)
		{
			char	*child_line;
			close(pfd[0]);
			struct sigaction	sa;

			sigemptyset(&sa.sa_mask);
			sa.sa_flags = 0;
			sa.sa_handler = restart_prompt;
			sigaction(SIGINT, &sa, (struct sigaction *) 0);
			child_line = readline(prompt);
			if (!child_line)
				exit((close(pfd[1]), 1));
			size_t	line_len = strlen(child_line);
			if (write(pfd[1], &line_len, sizeof(size_t)) == sizeof(size_t)
			&& write(pfd[1], child_line, line_len) == (ssize_t)line_len)
				exit((close(pfd[1]), free(child_line), 0));
			else
				exit((close(pfd[1]), free(child_line), \
				perror("write"), 42));
		}
		int	prompt_status;
		waitpid(prompt_id, &prompt_status, 0);
		close(pfd[1]);
		// fprintf(stderr, "prompt_status: %d\n", prompt_status);
		// fprintf(stderr, "WEXITSTATUS: %d\n", WEXITSTATUS(prompt_status));
		if (WEXITSTATUS(prompt_status) == 2)
		{
			close(pfd[0]);
			continue ;
		}
		if (WEXITSTATUS(prompt_status) == 1)
			exit((close(pfd[0]), 0)) ;
		if (WEXITSTATUS(prompt_status) == 42)
			exit((close(pfd[0]), 42));
		char	*line = NULL;
		size_t	len;
		if (read(pfd[0], &len, sizeof(size_t)) != sizeof(size_t))
			exit((perror("read"), 42));
		line = calloc(len + 1, sizeof(char));
		if (read(pfd[0], line, len) != (ssize_t)len)
			exit((perror("read"), 42));
		close(pfd[0]);
		// fprintf(stderr, "%s\n", line);
		add_history(line);
		int	j = -1;
		char	**line_argv = ft_split(line, ' ');
		while (path_list[++j])
		{
			memset(path, 0, PATH_MAX);
			memmove(path, path_list[j], strlen(path_list[j]));
			memmove(path + strlen(path_list[j]), "/", 1);
			memmove(path + strlen(path_list[j]) + 1, line_argv[0], strlen(line_argv[0]));
			if (!access(path, F_OK))
				break ;
		}
		if (!path_list[j]) {
			fprintf(stderr, "command not found: %s\n", line_argv[0]);
			continue ;
		}
		if (access(path, X_OK)) {
			fprintf(stderr, "permission denied: %s\n", line_argv[0]);
			continue ;
		}
		pid_t	id = fork();
		if (id == 0)
		{
			struct sigaction sa;

			sigemptyset(&sa.sa_mask);
			sa.sa_handler = quit_cmd;
			sigaction(SIGINT, &sa, (struct sigaction *)0);
			execve(path, line_argv, envp);
		}
		int	status;
		waitpid(id , &status, 0);
	}
	return (free(prompt), 0);
}
