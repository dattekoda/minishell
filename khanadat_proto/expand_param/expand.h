/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:58:48 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/14 05:01:03 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stddef.h>
# include "libft.h"
# ifndef ERR
#  define ERR -1
# endif
# ifndef SUCCESS
#  define SUCCESS 0
# endif
# define SPECIALS "$\'\"|"

typedef struct s_param
{
	char	*param;
	size_t	len;
}	t_param;

int	expand_params(char *line, char **expanded);
int	search_params(char *line, t_list **lst, size_t *expanded_len);
int	store_expanded(char *line, t_list *lst, \
	char **expanded, size_t expanded_len);

#endif