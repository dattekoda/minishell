#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	char			**cmd;
	struct s_list	*next;
	struct s_list	*before;
}	t_list;

int		cmd_n = 3;

void	dopipes(t_list *lst)
{
	pid_t	ret;
	int		pp[2] = {};
	if (!lst->before)
		execvp(lst->cmd[0], lst->cmd);
	else
	{
		pipe(pp);
		ret = fork();
		if (ret == 0)
		{
			close(pp[0]);
			dup2(pp[1], 1);
			close(pp[1]);

			dopipes(lst->before);
		}
		else
		{
			close(pp[1]);
			dup2(pp[0], 0);
			close(pp[0]);

			execvp(lst->cmd[0], lst->cmd);
		}
	}
}

int	main(void)
{
	char	*cmd1[] = {"cat", "test.c", NULL};
	char	*cmd2[] = {"head", NULL};
	char	*cmd3[] = {"grep", "char", NULL};
	t_list	lst3 = (t_list){cmd3, NULL};
	t_list	lst2 = (t_list){cmd2, &lst3};
	t_list	lst1 = (t_list){cmd1, &lst2};

	lst2.before = NULL;
	lst2.before = &lst1;
	lst3.before = &lst2;

	pid_t	ret = fork();
	if (ret == 0)
		dopipes(&lst3);
	else
		wait(NULL);
	return (0);
}
