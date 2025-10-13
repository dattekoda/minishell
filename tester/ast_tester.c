#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "ast_define.h"
#include "ast.h"
#include "tokenizer_define.h"
#include "tokenizer.h"
#include "minishell_utils.h"
#include "libft.h"

void	print_node(t_node *node)
{
	t_red	*r;
	t_word	*w;

	if (!node)
		return ;
	if (node->kind == ND_AND)
		ft_putstr_fd("and\n", 1);
	else if (node->kind == ND_OR)
		ft_putstr_fd("or\n", 1);
	else if (node->kind == ND_PIPE)
		ft_putstr_fd("pipe\n", 1);
	else if (node->kind == ND_INSIDE)
		ft_putstr_fd("inside\n", 1);
	else if (node->kind == ND_CMD)
	{
		ft_putstr_fd("cmd: ", 1);
		w = node->word;
		while (w)
		{
			ft_putstr_fd(w->word, 1);
			ft_putchar_fd(' ', 1);
			w = w->next;
		}
		ft_putchar_fd('\n', 1);
		r = node->red;
		while (r)
		{
			if (r->kind == RD_APPEND)
				ft_putstr_fd("append: ", 1);
			else if (r->kind == RD_HEREDOC)
				ft_putstr_fd("heredoc: ", 1);
			else if (r->kind == RD_IN)
				ft_putstr_fd("redirect in: ", 1);
			else if (r->kind == RD_OUT)
				ft_putstr_fd("redirect_out: ", 1);
			ft_putendl_fd(r->file, 1);
			r = r->next;
		}
	}
	if (node->lhs)
	{
		// ft_putstr_fd("left\n", 1);
		print_node(node->lhs);
	}
	if (node->rhs)
	{
		// ft_putendl_fd("right", 1);
		print_node(node->rhs);
	}
}

int	main(void) {
	char	*line;
	t_token	*token;
	t_node	*node;
	int		status;

	while (1) {
		line = readline("$ ");
		if (!line)
			break ;
		add_history(line);
		status = get_token(&token, line);
		if (status < 0)
			return (free(line), FAILURE);
		if (status == SYNTAX_ERR)
		{
			free(line);
			continue ;
		}
		status = get_node(&node, token);
		if (status < 0)
			return (free_token((t_token **)&token), free(line), FAILURE);
		if (status == SYNTAX_ERR)
		{
			free_token(&token);
			free(line);
			continue ;
		}
		free_token(&token);
		print_node(node);
		free_node(&node);
		free(line);
	}
	rl_clear_history();
	return (SUCCESS);
}
