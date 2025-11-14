/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:34 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/01 21:20:16 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast_define.h"
# include "tokenizer_define.h"

// ast_utils_cmd.c
void	free_word(t_word *head);

// ast_utils_red.c
void	free_red(t_red *head);

void	free_node(t_node **node);
int		get_node(t_node **node, t_token *token);

#endif