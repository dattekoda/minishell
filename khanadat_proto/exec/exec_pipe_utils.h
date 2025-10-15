/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:38:13 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/15 13:35:12 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPE_UTILS_H
# define EXEC_PIPE_UTILS_H

# include "ast_define.h"

t_node	*set_cmd_order(t_node *node);
void	start_pipe_group(t_mini *mini, t_node *node);
void	wait_pipe_group(t_mini *mini, t_node *node);

#endif