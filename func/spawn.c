#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <command> <arg>\n", argv[0]);
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork(2) failed\n");
		exit(1);
	}
	// 子プロセスの処理
	if (pid == 0) {
		// 第一引数がパス、それ以降はコマンドをコマンドライン引数の形で受け取る。
		execl(argv[1], argv[1], argv[2], NULL);
		// execlが正しく終了していなかったときのみ、perrorが読まれる。
		perror((argv[1]));
		exit(99);
	}
	// 親プロセス
	else {
		int status;

		// statusに子プロセスの終了ステータスの情報が格納される。
		waitpid(pid, &status, 0);
		printf("child (PID=%d) finished; ", pid);
		// WIFEXITEDが真のとき子プロセスは正常終了
		if (WIFEXITED(status))
		// WEXITSTATUSは子プロセスの終了ステータスを取得する。
			printf("exit, status=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("signal, sig=%d\n", WTERMSIG(status));
		else
			printf("abnormal exit\n");
		exit(0);
	}
}