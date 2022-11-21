/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_light_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:29:21 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:29:29 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "minirt.h"
#include "parse.h"
#include "vector.h"

#include <stdio.h>
#include <stdbool.h>

bool	edit_ambient_light(int key_input, t_vars *vars)
{
	if (key_input == KEY_MINUS)
	{
		printf("Brightness: -0.1\n");
		vec_minus(&vars->descr.al.cr, vars->descr.al.cr,
			vec_set(0.1, 0.1, 0.1));
		return (true);
	}
	else if (key_input == KEY_PLUS)
	{
		printf("Brightness: +0.1\n");
		vec_plus(&vars->descr.al.cr, vars->descr.al.cr, vec_set(0.1, 0.1, 0.1));
		return (true);
	}
	return (false);
}

bool	edit_light(int key_input, t_vars *vars)
{
	bool	ret;

	if (key_input == KEY_MINUS)
	{
		printf("Brightness: -0.1\n");
		vec_minus(&vars->descr.l.cb, vars->descr.l.cb, vec_set(0.1, 0.1, 0.1));
		return (true);
	}
	else if (key_input == KEY_PLUS)
	{
		printf("Brightness: +0.1\n");
		vec_plus(&vars->descr.l.cb, vars->descr.l.cb, vec_set(0.1, 0.1, 0.1));
		return (true);
	}
	else
		ret = edit_move(key_input, vars->descr.c.o, &vars->descr.l.p);
	return (ret);
}

bool	edit_camera(int key_input, t_vars *vars)
{
	bool	ret;

	ret = false;
	if (key_input == KEY_I || key_input == KEY_J
		|| key_input == KEY_K || key_input == KEY_L)
		ret = edit_rotation(key_input, &vars->descr.c.o);
	if (key_input == KEY_Q || key_input == KEY_W || key_input == KEY_E
		|| key_input == KEY_A || key_input == KEY_S || key_input == KEY_D)
		ret = edit_move(key_input, vars->descr.c.o, &vars->descr.c.p);
	return (ret);
}
