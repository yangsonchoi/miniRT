/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:43:06 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 11:43:09 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

#include <math.h>

void	vec_move_side(t_vec3 *dest, t_vec3 input)
{
	t_vec3	temp;

	temp.x = input.z;
	temp.y = 0;
	temp.z = -1 * input.x;
	vec_convert_unit(temp, &temp);
	vec_div_db(dest, temp, 0.5);
}

void	vec_move_front(t_vec3 *dest, t_vec3 input)
{
	t_vec3	temp;

	temp.x = input.x;
	temp.y = 0;
	temp.z = input.z;
	vec_convert_unit(temp, &temp);
	vec_div_db(dest, temp, 0.5);
}

void	vec_rotate(t_vec3 *dest, int axis, int sign)
{
	t_vec3	temp;
	double	step;

	temp = *dest;
	step = M_PI / 12 * sign;
	if (axis == 0)
	{
		dest->y = temp.y * cos(step) + temp.z * sin(step);
		dest->z = temp.z * cos(step) - temp.y * sin(step);
	}
	if (axis == 1)
	{
		dest->x = temp.x * cos(step) - temp.z * sin(step);
		dest->z = temp.z * cos(step) + temp.x * sin(step);
	}
	if (axis == 2)
	{
		dest->x = temp.x * cos(step) + temp.y * sin(step);
		dest->y = temp.y * cos(step) - temp.x * sin(step);
	}
}
