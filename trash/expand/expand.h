/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:58:48 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/16 16:11:17 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stddef.h>
# include "libft.h"
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