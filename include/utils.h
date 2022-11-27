/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:12:45 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/27 12:12:46 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"
# include <stdbool.h>

/*
** free.c
*/
void	free_dcharp(char **input);
void	free_description(t_descr *descr);

/*
** error.c
*/
void	err_exit(char *str, int input);
void	err_exit_descr(t_descr *descr, char **input);

/*
** get_next_line.c
*/
char	*get_next_line(int fd);

/*
** check.c
*/
bool	check_dcharp_num(int i, char **input);
bool	check_syntax_dbl(char *input);
bool	check_syntax_vec(char *input);
bool	check_syntax_rgb(char *input);

#endif
