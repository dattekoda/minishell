/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 09:45:18 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 14:19:10 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include <stddef.h>
# include "minishell_define.h"
# include "ast_define.h"

// exec_utils0.c
int		store_argv(t_word *head, char ***argv);
void	exec_child_proc(t_mini *mini, char **argv);
void	set_rfd(t_mini *mini, t_cmd *cmd);
void	exec_cmd(t_mini *mini, t_node *node);
void	reset_rfd(t_mini *mini, t_node *node);

// exec_utils2.c
void	exec_inside(t_mini *mini, t_node *node);
void	wait_node(t_mini *mini, t_node *node);

// exec_pipe.c
void	exec_node(t_mini *mini, t_node *node);

#endif