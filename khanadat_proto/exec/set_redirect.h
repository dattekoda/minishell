/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:22:50 by khanadat          #+#    #+#             */
/*   Updated: 2025/10/07 17:58:03 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_REDIRECT_H
# define SET_REDIRECT_H

# include "minishell_define.h"

int	set_redirect(t_mini *mini, t_red *red, t_cmd *cmd);
int	write_heredoc(t_mini *mini, t_red *red, t_cmd *cmd);

#endif