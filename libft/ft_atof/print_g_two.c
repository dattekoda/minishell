#include <stdio.h>
int	main(void) {
	for (int i = 1; i < 109; i++) {
		printf("T_M_%d,", i);
		printf(" ");
		if ((i - 0) % 8 == 0)
			printf("\\\n");
	}
}