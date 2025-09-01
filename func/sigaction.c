#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

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
	printf("Got signall %d\n", sig);
	exit(0);
}

int	main(int argc, char *argv[])
{
	trap_signal(SIGINT, print_exit);
	// signal(SIGINT, print_exit);
	while (1)
		printf("ohayo");
	exit(0);
}