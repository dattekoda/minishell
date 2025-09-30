/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:29:53 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/30 15:36:36 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ast.h"
# include "minishell_define.h"

void	exec_cmd(t_mini *mini, t_node *node);
void	exec_prompt(t_mini *mini, t_node *node/* , t_NodeKind nkind */);

#endif