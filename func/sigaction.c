#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
// void	do_nothin(int sig)
// {
// }

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;

	if (argc != 1)
		exit(1);
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, (struct sigaction *) 0);

	int	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5))
			i++;
		break ;
	}
	if (!envp[i])
		exit(2);
	char	**path_list;
	char	*path_start = strchr(envp[i], '=') + 1;
	char	*path_end;
	while ((path_end = strchr(path_start + 1, ':')) != NULL)
	{
		
	}

	char	*program_name;
	program_name = strchr(argv[0], '/');
	if (!program_name)
		exit(3);
	size_t	program_name_len = strlen(program_name);
	prompt = calloc(program_name_len + 3, sizeof(char));
	memmove(prompt, program_name, program_name_len);
	memmove(prompt + program_name_len, "$ ", 2);

	char	*line;
	while (1)
	{
		line = readline(prompt);
		if (!line)
			break ;
	}
	return (free(prompt), 0);
}
