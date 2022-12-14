/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cal1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:45:02 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 11:45:04 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

#include <math.h>

void	vec_plus(t_vec3 *dest, t_vec3 a, t_vec3 b)
{
	dest->x = a.x + b.x;
	dest->y = a.y + b.y;
	dest->z = a.z + b.z;
}

void	vec_minus(t_vec3 *dest, t_vec3 a, t_vec3 b)
{
	dest->x = a.x - b.x;
	dest->y = a.y - b.y;
	dest->z = a.z - b.z;
}

void	vec_mul_vec(t_vec3 *dest, t_vec3 a, t_vec3 b)
{
	dest->x = a.x * b.x;
	dest->y = a.y * b.y;
	dest->z = a.z * b.z;
}

void	vec_mul_db(t_vec3 *dest, t_vec3 a, double b)
{
	dest->x = a.x * b;
	dest->y = a.y * b;
	dest->z = a.z * b;
}

void	vec_div_db(t_vec3 *dest, t_vec3 a, double b)
{
	dest->x = a.x / b;
	dest->y = a.y / b;
	dest->z = a.z / b;
}
