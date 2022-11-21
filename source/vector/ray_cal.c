/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:42:00 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 11:42:52 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"
#include "draw.h"

#include <math.h>
#include <stdbool.h>

void	ray_at(t_vec3 *dest, t_ray a, double b)
{
	t_vec3	temp;

	vec_mul_db(&temp, a.dir, b);
	vec_plus(dest, a.p, temp);
}

void	set_face(t_ray ray, t_rec *rec)
{
	rec->face = vec_dot(ray.dir, rec->norm) < 0;
	if (rec->face == false)
		vec_mul_db(&rec->norm, rec->norm, -1);
}

void	max_color(t_vec3 *dest, t_vec3 color)
{
	if (color.x > 255.0)
		dest->x = 255;
	else
		dest->x = color.x;
	if (color.y > 255.0)
		dest->y = 255;
	else
		dest->y = color.y;
	if (color.z > 255.0)
		dest->z = 255;
	else
		dest->z = color.z;
}
