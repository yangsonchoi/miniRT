/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:12:30 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/27 12:12:32 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"
# include "draw.h"

/*
** vector_cal1.c
*/
void	vec_plus(t_vec3 *dest, t_vec3 a, t_vec3 b);
void	vec_minus(t_vec3 *dest, t_vec3 a, t_vec3 b);
void	vec_mul_vec(t_vec3 *dest, t_vec3 a, t_vec3 b);
void	vec_mul_db(t_vec3 *dest, t_vec3 a, double b);
void	vec_div_db(t_vec3 *dest, t_vec3 a, double b);

/*
** vector_cal2.c
*/
double	vec_dot(t_vec3 a, t_vec3 b);
void	vec_cross(t_vec3 *dest, t_vec3 a, t_vec3 b);
double	vec_convert_unit(t_vec3 input, t_vec3 *dest);
t_vec3	vec_set(double x, double y, double z);
t_color	color_set(double x, double y, double z);

/*
** vector_cal3.c
*/
void	vec_move_side(t_vec3 *dest, t_vec3 input);
void	vec_move_front(t_vec3 *dest, t_vec3 input);
void	vec_rotate(t_vec3 *dest, int axis, int sign);

/*
** ray_cal.c
*/
void	ray_at(t_vec3 *dest, t_ray a, double b);
void	set_face(t_ray ray, t_rec *rec);
void	max_color(t_vec3 *dest, t_vec3 color);

#endif
