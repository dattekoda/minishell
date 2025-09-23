#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

// struct sigaction {
// 	void		(*sa_handler)(int); // シグナルを受けたときの処理
// 	void		(*sa_sigaction)(int, siginfo_t *, void *); // 詳細情報付きの処理
// 	sigset_t	sa_mask;            // 処理中にブロックするシグナル
// 	int			sa_flags;           // 動作フラグ
// };


// sigaction関数はsigalがプロセスに送られたときの挙動を指定するためのシステムコール
// 従来のsignal関数よりも細かく安全に制御できる。
// signalは環境依存

// sigaction関数はOSに関わらずシグナルハンドラの設定を保持し続けることが保証されている。
// sigaction関数はデフォルトではシステムコールを再起動しない。
// sa_flagsメンバにフラグSA_RESTARTを追加すると、再起動する設定になる。

typedef void	(*sighandler_t)(int);

sighandler_t	trap_signal(int sig, sighandler_t handler)
{
	struct sigaction act, old;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	if (sigaction(sig, &act, &old) < 0)
		return (NULL);
	return old.sa_handler;
}

void	print_exit(int sig)
{
	exit(sig + 128);
}

void	set_prompt(int sig)
{
	char	*prompt;

	(void)sig;
	prompt = readline("$ ");
}

#define FILE_NAME ".heredoc_test"

int	main(void)
{
	trap_signal(SIGINT, SIG_IGN);
	// signal(SIGINT, print_exit);
	while (1)
	{
		char	*prompt;
		int		status;
		pid_t	d;

		prompt = readline("$ ");
		if (!prompt)
			break ;
		if (ft_strncmp(prompt, "heredoc", 7))
		{
			free(prompt);
			continue ;
		}
		d = fork();
		if (d == 0)
		{
			char	*line;
			int		fd;
			int		gnl;
			fd = open(FILE_NAME, O_RDWR | O_CREAT, 0644);
			trap_signal(SIGINT, print_exit);
			while (1)
			{
				ft_putstr_fd("heredoc > ", 1);
				ft_get_next_line(0, &line);
				if (!line)
					break ;
				write(fd, line, ft_strlen(line));
				free(line);
			}
			close(fd);
			fd = open(FILE_NAME, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				exit(54);
			}
			ft_putchar_fd('\n', 1);
			while ((gnl = ft_get_next_line(fd, &line)) == 1) {
				ft_putstr_fd(line, 1);
				free(line);
			}
			close(fd);
			unlink(FILE_NAME);
		}
		waitpid(d, &status, 0);
	}
	exit(0);
}