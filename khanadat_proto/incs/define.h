/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:22:39 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/08 22:22:45 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define PROMPT " $"

typedef struct s_stree t_tree;

typedef struct s_tree
{
	char	*cmd;
	char	*path;
}	t_tree;

typedef struct s_data
{
	int	cmmd_num;
}	t_data;

typedef struct s_arg
{
	int		c;
	char	**v;
	char	**e;
}	t_arg;

typedef struct s_prompt
{
	t_arg	*arg;
	char	*shell_name;
	char	*cmd_line;
	int		num_cmds;
}	t_prompt;

#endif