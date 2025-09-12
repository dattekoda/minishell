/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:02:56 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/10 01:10:56 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

char	*pwd();
void	print_pwd(void);
void	echo(int argc, char *argv[]);
int		cd(int argc, char *argv[], char *envp[]);

#endif