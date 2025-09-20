#ifndef TOKENIZER_UTILS_H
# define TOKENIZER_UTILS_H

# include "tokenizer_define.h"

// tokenizer_utils.c
t_token	*new_reserved_token(t_token *cur, char **str);
int		skip_word(char **str);
t_token	*new_word_token(t_token *cur, char **str);
t_token	*new_eof_token(t_token *cur);

// tokenizer_validate.c
int		syntax_validate(char *line);

#endif