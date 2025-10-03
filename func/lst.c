#include "libft.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*list;
	t_list	head;

	argc = *(int *)(void *)&argc;
	argv = (char **)(void *)&argv;
	ft_bzero(&head, sizeof(t_list));
	list = &head;
	for (size_t i = 0; envp[i]; i++) {
		ft_lstadd_back(&list, ft_lstnew(envp[i]));
	}
	ft_lstclear(&head.next, NULL);
	printf("%s\n", (char *)list->next->content);
	return (0);
}
