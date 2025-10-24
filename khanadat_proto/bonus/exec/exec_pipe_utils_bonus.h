/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:38:13 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPE_UTILS_BONUS_H
# define EXEC_PIPE_UTILS_BONUS_H

# include "ast_define_bonus.h"

t_node	*set_cmd_order(t_node *node);
void	start_pipe_group(t_mini *mini, t_node *node);
void	wait_pipe_group(t_mini *mini, t_node *node);

#endif