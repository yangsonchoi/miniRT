#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

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

#endif