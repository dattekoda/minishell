/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:02:56 by khanadat          #+#    #+#             */
/*   Updated: 2025/09/10 17:24:20 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

char	*pwd();
int		print_pwd(void);
int		builtin_echo(int argc, char *argv[]);
int		builtin_cd(int argc, char *argv[], char *home);

#endif