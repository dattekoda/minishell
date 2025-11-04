
// #include "expand_define.h"
// #include "expand.h"
// #include <unistd.h>
// #include <stdio.h>

// void	dol_checker(t_dollar *dol)
// {
// 	while (dol)
// 	{
// 		if (dol->dkind == WD_WORD)
// 		{
// 			fprintf(stderr, "val:	%s\n", dol->value);
// 			fprintf(stderr, "len:	%zu\n", dol->value_len);
// 		}
// 		else if (dol->dkind == WD_SPACE)
// 			fprintf(stderr, "space\n");
// 		fprintf(stderr, "\n");
// 		dol = dol->next;
// 	}
// }
