#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// signal関数はいくつか重大な欠陥を抱えている。
// 一部の古いOSだと、signal()で登録したハンドラは一回シグナルを処理すると
// 自動的にデフォルトに戻る仕様だった。このせいで意図せずにシグナルを見逃す危険性がある。
// シグナルはプログラムがread(2)やwrite(2)を実行中でも割り込んでくる。
// このときの挙動がOSによってバラバラ。
// シグナルハンドラはプログラムの実行中どこでも割り込んで動くので、
// ハンドラ内部では「安全だと保証されるごく一部音関数」しか呼んではいけない。

void	handler1(int signal)
{}

void	handler2(int signal)
{
	write(1, "6", 1);
	alarm(5);
	write(1, "7", 1);
}

int	main()
{
	write(1, "1", 1);
	signal(SIGINT, handler1);
	write(1, "2", 1);
	signal(SIGALRM, handler2);
	write(1, "3", 1);
	alarm(2);
	write(1, "4", 1);
	while (1)
		;
	write(1, "5", 1);
	return (0);
}