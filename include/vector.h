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
** ray_cal.c
*/
void	ray_at(t_vec3 *dest, t_ray a, double b);
void	set_face(t_ray ray, t_rec *rec);

#endif