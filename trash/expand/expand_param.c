/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:08:01 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/16 16:33:25 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "expand.h"
#include "status.h"

static void	param_free(void *ptr);

// success 0 err -1
int	expand_params(char *line, char **expanded)
{
	t_list	*lst;
	size_t	expanded_len;

	expanded_len = 0;
	lst = NULL;
	if (search_params(line, &lst, &expanded_len))
		return (free(line), ft_lstclear(&lst, param_free), ERR);
	if (store_expanded(line, lst, expanded, expanded_len))
		return (free(line), ft_lstclear(&lst, param_free), ERR);
	return (free(line), ft_lstclear(&lst, param_free), SUCCESS);
}

static void	param_free(void *ptr)
{
	t_param	*param;

	param = (t_param *)ptr;
	if (param && param->param)
		free(param->param);
	if (param)
		free(param);
}
