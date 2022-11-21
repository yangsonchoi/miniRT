/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:20:29 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:20:30 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"
#include "minirt.h"
#include "parse.h"

#include <stdio.h>
#include <stdbool.h>

static void	edit_object_type(int key_input, t_vars *vars);
static void	edit_object_instruction(t_vars *vars);

bool	edit_mode(int key_input, t_vars *vars)
{
	bool	ret;

	ret = false;
	if (vars->edit.obj == EMPTY)
		edit_object_type(key_input, vars);
	else if (vars->edit.obj == AMBIENT_LIGHT)
		ret = edit_ambient_light(key_input, vars);
	else if (vars->edit.obj == CAMERA)
		ret = edit_camera(key_input, vars);
	else if (vars->edit.obj == LIGHT)
		ret = edit_light(key_input, vars);
	else if (vars->edit.obj == SPHERE || vars->edit.obj == PLANE
		|| vars->edit.obj == CYLINDER)
		ret = edit_object(key_input, vars);
	else
	{
		printf("\nWrong object\nReset edit object\n");
		vars->edit.obj = EMPTY;
	}
	return (ret);
}

void	edit_on(t_vars *vars)
{
	printf("\nEdit mode: ON\n\nAmbient light: a\nCamera: c\n\
		Light: l\nSphere: s\nplane: p\ncylinder y\nEnd edit: Enter\n");
	vars->edit.stat = true;
	vars->edit.obj = EMPTY;
	vars->edit.num = -1;
	vars->edit.opt = 0;
}

void	edit_off(t_vars *vars)
{
	printf("\nEdit parameter reset\nEdit mode: off\n");
	vars->edit.stat = false;
	vars->edit.obj = EMPTY;
	vars->edit.num = -1;
	vars->edit.opt = 0;
}

static void	edit_object_type(int key_input, t_vars *vars)
{
	if (key_input == KEY_A)
		vars->edit.obj = AMBIENT_LIGHT;
	else if (key_input == KEY_C)
		vars->edit.obj = CAMERA;
	else if (key_input == KEY_L)
		vars->edit.obj = LIGHT;
	else if (key_input == KEY_S)
		vars->edit.obj = SPHERE;
	else if (key_input == KEY_P)
	{
		if (vars->descr.cnt.pl_cnt == 0)
			printf("\nNo plane in the scene\n");
		else
			vars->edit.obj = PLANE;
	}
	else if (key_input == KEY_Y)
	{
		if (vars->descr.cnt.pl_cnt == 0)
			printf("\nNo cylinder in the scene\n");
		else
			vars->edit.obj = CYLINDER;
	}
	if (vars->edit.obj != EMPTY)
		edit_object_instruction(vars);
}

static void	edit_object_instruction(t_vars *vars)
{
	if (vars->edit.obj == AMBIENT_LIGHT)
		printf("\nObject set: Ambient light\n\nbrightness: +-\n");
	else if (vars->edit.obj == CAMERA)
		printf("\nObject set: Camera\n\nMove: QWEASD\nRotate: IJKL\n");
	else if (vars->edit.obj == LIGHT)
		printf("\nObject set: Light\n\nMove: QWEASD\nbrightness: +-\n");
	else if (vars->edit.obj == SPHERE)
	{
		if (vars->descr.cnt.sp_cnt == 0)
		{
			printf("\nNo shpere in the scene\n");
			vars->edit.obj = EMPTY;
		}
		else
			printf("\nObject set: Sphere\n\n Set sphere num: [0,%d]\n",
				vars->descr.cnt.sp_cnt - 1);
	}
	else if (vars->edit.obj == PLANE)
		printf("\nObject set: Plane\n\n Set plane num: [0,%d]\n",
			vars->descr.cnt.pl_cnt - 1);
	else if (vars->edit.obj == CYLINDER)
		printf("\nObject set: Cylinder\n\n Set cylinder num: [0,%d]\n",
			vars->descr.cnt.cy_cnt - 1);
}
