#include "edit.h"
#include "minirt.h"
#include "vector.h"

#include <stdio.h>
#include <stdbool.h>

bool	edit_move(int key_input, t_vec3 cam, t_vec3 *pos)
{
	bool	ret;

	ret = true;
	if (key_input == KEY_A || key_input == KEY_D)
	{
		vec_move_side(&cam, cam);
		if (key_input == KEY_A)
			vec_minus(pos, *pos, cam);
		else if (key_input == KEY_D)
			vec_plus(pos, *pos, cam);
	}
	else if (key_input == KEY_W || key_input == KEY_S)
	{
		vec_move_front(&cam, cam);
		if (key_input == KEY_W)
			vec_minus(pos, *pos, cam);
		else if (key_input == KEY_S)
			vec_plus(pos, *pos, cam);
	}
	else if (key_input == KEY_Q)
		vec_minus(pos, *pos, vec_set(0, 0.5, 0));
	else if (key_input == KEY_E)
		vec_plus(pos, *pos, vec_set(0, 0.5, 0));
	else
		ret = false;
	return (ret);
}

bool	edit_rotation(int key_input, t_vec3 *orient)
{
	bool	ret;

	ret = true;
	if (key_input == KEY_J)
		vec_rotate(orient, 1, -1);
	else if (key_input == KEY_L)
		vec_rotate(orient, 1, 1);
	else if (key_input == KEY_I)
		vec_rotate(orient, 0, -1);
	else if (key_input == KEY_K)
		vec_rotate(orient, 0, 1);
	else if (key_input == KEY_U)
		vec_rotate(orient, 2, -1);
	else if (key_input == KEY_O)
		vec_rotate(orient, 2, 1);
	else
		ret = false;
	return (ret);
}

int	convert_num_key(int key_input)
{
	if (key_input == KEY_0)
		return (0);
	else if (key_input == KEY_1)
		return (1);
	else if (key_input == KEY_2)
		return (2);
	else if (key_input == KEY_3)
		return (3);
	else if (key_input == KEY_4)
		return (4);
	else if (key_input == KEY_5)
		return (5);
	else if (key_input == KEY_6)
		return (6);
	else if (key_input == KEY_7)
		return (7);
	else if (key_input == KEY_8)
		return (8);
	else if (key_input == KEY_9)
		return (9);
	return (-1);
}

bool	edit_size(int sign, double *size)
{
	*size = *size + 0.5 * sign;
	return (true);
}
