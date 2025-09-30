/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:34 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/29 19:36:00 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_define.h"
# include "tokenizer_define.h"

// ast_utils_cmd.c
void	free_word(t_word *head);

void	free_node(t_node **node);
int		get_node(t_node **node, t_token *token);

#endif