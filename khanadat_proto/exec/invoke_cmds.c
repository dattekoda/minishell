#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"
#include "ast.h"
#include "status.h"
#include "libft.h"

void	consume_node(t_mini *mini, t_node *node)
{
	if (mini->node->lhs)
		consume_node(mini, mini->node->lhs);
	if (node->kind == ND_CMD)
	{
		
	}
	// else if (node->kind == ND_PIPE)
	// else if (node->kind == ND_OR)
	// else if (node->kind == ND_AND)
}

void	invoke_cmds(t_mini *mini)
{
}
