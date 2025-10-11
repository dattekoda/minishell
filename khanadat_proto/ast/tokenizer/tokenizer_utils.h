/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 09:58:56 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/11 23:03:01 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "tokenizer_define.h"

// tokenizer_utils.c
t_token	*new_op_token(t_token *cur, char **str);
int		skip_word(char **str);
t_token	*new_word_token(t_token *cur, char **str);
t_token	*new_eof_token(t_token *cur);

// tokenizer_validate.c
int		validate_b4_tokenize(char *line);

#endif