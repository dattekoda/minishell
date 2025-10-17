/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:05:35 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/16 22:48:41 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_REDIRECT_UTILS_H
# define SET_REDIRECT_UTILS_H

# include "minishell_define.h"

char	*set_heredoc_name(int num);
int		expand_dollar(t_mini *mini, char **line);
void	sys_hd_exit(t_mini *mini, char *hd_name, int fd, char *func);

// set_redirect_utils1.c
bool	is_end_heredoc(char *line, t_red *red);

#endif