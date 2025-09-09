/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/09 20:26:10 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ERR 1
# define SUCCESS 0
# define PROMPT " $"

// typedef struct s_stree t_tree;

// typedef struct s_tree
// {
// 	char	*cmd;
// 	char	*path;
// }	t_tree;

typedef struct s_arg
{
	int		c;
	char	**v;
	char	**e;
}	t_arg;

typedef struct s_prompt
{
	char	*cmd_line;
	char	**split_cmd_line;
	int		num_word;
	int		num_cmd;
	int		num_pipe;
	int		num_or_op;
}	t_prompt;

typedef struct s_data
{
	t_arg		*arg;
	char		*shell_name;
	t_prompt	*prompt;
}	t_data;

#endif