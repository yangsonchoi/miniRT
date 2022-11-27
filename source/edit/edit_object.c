/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:26:22 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:26:23 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "minirt.h"
#include "parse.h"
#include "vector.h"

#include <stdio.h>
#include <stdbool.h>

static void	edit_set_num(int key_input, t_vars *vars);
static bool	edit_sphere(int key_input, t_vec3 cam, t_sphere *sp);
static bool	edit_plane(int key_input, t_vec3 cam, t_plane *pl);
static bool	edit_cylinder(int key_input, t_vec3 cam, t_cylinder *cy);

bool	edit_object(int key_input, t_vars *vars)
{
	bool	ret;

	ret = false;
	if (vars->edit.num == -1 && ((key_input >= 18 && key_input <= 23)
			|| (key_input >= 25 && key_input <= 29 && key_input != 27)))
	{
		edit_set_num(key_input, vars);
		if (vars->edit.num == -1)
			printf("\nOut of range\nRetry differnt number\n");
	}
	else if (!(vars->edit.num == -1) && vars->edit.obj == SPHERE)
		ret = edit_sphere(key_input, vars->descr.c.o,
				vars->descr.sp[vars->edit.num]);
	else if (!(vars->edit.num == -1) && vars->edit.obj == PLANE)
		ret = edit_plane(key_input, vars->descr.c.o,
				vars->descr.pl[vars->edit.num]);
	else if (!(vars->edit.num == -1) && vars->edit.obj == CYLINDER)
		ret = edit_cylinder(key_input, vars->descr.c.o,
				vars->descr.cy[vars->edit.num]);
	return (ret);
}

static void	edit_set_num(int key_input, t_vars *vars)
{
	int	i;

	i = convert_num_key(key_input);
	if (vars->edit.obj == SPHERE && (i < vars->descr.cnt.sp_cnt))
	{
		vars->edit.num = i;
		printf("\nSphere #%d slected\nMove: QWEASD\nSize: +,-\n", i);
	}
	else if (vars->edit.obj == PLANE && (i < vars->descr.cnt.pl_cnt))
	{
		vars->edit.num = i;
		printf("\nPlane #%d slected\nMove: QWEASD\nRotate: UIOJKL\n", i);
	}
	else if (vars->edit.obj == CYLINDER && (i < vars->descr.cnt.cy_cnt))
	{
		vars->edit.num = i;
		printf("\nCylinder #%d slected\nMove: QWEASD\n", i);
		printf("Rotate: UIOJKL\nlength: -,+\nSize: 5,6\n");
	}
}

static bool	edit_sphere(int key_input, t_vec3 cam, t_sphere *sp)
{
	bool	ret;

	ret = false;
	if (key_input == KEY_Q || key_input == KEY_W || key_input == KEY_E
		|| key_input == KEY_A || key_input == KEY_S || key_input == KEY_D)
		ret = edit_move(key_input, cam, &sp->p);
	else if (key_input == KEY_MINUS)
		ret = edit_size(-1, &sp->r);
	else if (key_input == KEY_PLUS)
		ret = edit_size(1, &sp->r);
	return (ret);
}

static bool	edit_plane(int key_input, t_vec3 cam, t_plane *pl)
{
	bool	ret;

	ret = false;
	if (key_input == KEY_Q || key_input == KEY_W || key_input == KEY_E
		|| key_input == KEY_A || key_input == KEY_S || key_input == KEY_D)
		ret = edit_move(key_input, cam, &pl->p);
	if (key_input == KEY_I || key_input == KEY_J || key_input == KEY_K
		|| key_input == KEY_L || key_input == KEY_U || key_input == KEY_O)
		ret = edit_rotation(key_input, &pl->o);
	return (ret);
}

static bool	edit_cylinder(int key_input, t_vec3 cam, t_cylinder *cy)
{
	bool	ret;

	ret = false;
	if (key_input == KEY_Q || key_input == KEY_W || key_input == KEY_E
		|| key_input == KEY_A || key_input == KEY_S || key_input == KEY_D)
		ret = edit_move(key_input, cam, &cy->p);
	if (key_input == KEY_I || key_input == KEY_J || key_input == KEY_K
		|| key_input == KEY_L || key_input == KEY_U || key_input == KEY_O)
		ret = edit_rotation(key_input, &cy->o);
	else if (key_input == KEY_MINUS)
		ret = edit_size(-1, &cy->h);
	else if (key_input == KEY_PLUS)
		ret = edit_size(1, &cy->h);
	else if (key_input == KEY_5)
		ret = edit_size(-1, &cy->r);
	else if (key_input == KEY_6)
		ret = edit_size(1, &cy->r);
	return (ret);
}
