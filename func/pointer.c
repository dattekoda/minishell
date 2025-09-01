#include <stdio.h>
#include <stdlib.h>

int	plus(int n)
{
	return (n + 1);
}

int	main(int argc, char *argv[])
{
	int	(*f)(int);
	int	result;

	// plusの関数ポインタを変数fに代入している。
	// plusを呼んでいるわけではない。
	f = plus;
	result = f(5);
	printf("%d\n", result);
	exit(0);
}
