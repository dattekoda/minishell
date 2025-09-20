#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokenizer_define.h"

int		get_token(t_token **cur, char *line);
void	free_token(t_token *token);

#endif