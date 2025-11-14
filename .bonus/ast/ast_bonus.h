/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:34 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/24 20:59:29 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BONUS_H
# define AST_BONUS_H

# include "ast_define_bonus.h"
# include "tokenizer_define_bonus.h"

// ast_utils_cmd.c
void	free_word(t_word *head);

// ast_utils_red.c
void	free_red(t_red *head);

void	free_node(t_node **node);
int		get_node(t_node **node, t_token *token);

#endif