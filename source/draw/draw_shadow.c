/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:36:03 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:36:05 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static double	set_shadow_ray(t_ray *ray, t_rec rec, t_descr *descr);
static bool		hit_sphere_shadow(t_ray ray, t_sphere *sp, double t_max);
static bool		hit_plane_shadow(t_ray ray, t_plane *pl, double t_max);

bool	hit_object_shadow(t_rec rec, t_descr *descr)
{
	int		i;
	t_ray	ray;
	double	t_max;

	i = 0;
	t_max = set_shadow_ray(&ray, rec, descr);
	if (descr->sp != NULL)
	{
		while (descr->sp[i] != NULL)
			if (hit_sphere_shadow(ray, descr->sp[i++], t_max) == true)
				return (true);
	}
	i = 0;
	if (descr->pl != NULL)
	{
		while (descr->pl[i] != NULL)
			if (hit_plane_shadow(ray, descr->pl[i++], t_max) == true)
				return (true);
	}
	if (descr->cy != NULL)
	{
		if (cylinder_shadow(ray, descr, t_max) == true)
			return (true);
	}
	return (false);
}

static double	set_shadow_ray(t_ray *ray, t_rec rec, t_descr *descr)
{
	double	light_len;

	ray->p = rec.p;
	vec_minus(&ray->dir, descr->l.p, ray->p);
	light_len = sqrt(vec_dot(ray->dir, ray->dir));
	vec_convert_unit(ray->dir, &ray->dir);
	return (light_len);
}

static bool	hit_sphere_shadow(t_ray ray, t_sphere *sp, double t_max)
{
	t_vec3	oc;
	double	discriminant;
	double	a;
	double	half_b;
	double	root;

	vec_minus(&oc, ray.p, sp->p);
	a = vec_dot(ray.dir, ray.dir);
	half_b = vec_dot(oc, ray.dir);
	discriminant = pow(half_b, 2) - (a * (vec_dot(oc, oc) - pow(sp->r, 2)));
	if (discriminant < 0)
		return (false);
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < MIN || root > t_max)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < MIN || root > t_max)
			return (false);
	}
	return (true);
}

static bool	hit_plane_shadow(t_ray ray, t_plane *pl, double t_max)
{
	double	discriminant;
	double	d;
	double	t;

	discriminant = vec_dot(pl->o, ray.dir);
	if (discriminant < MIN && -1 * discriminant < MIN)
		return (false);
	d = vec_dot(pl->o, pl->p);
	t = (d - vec_dot(pl->o, ray.p)) / discriminant;
	if (t < MIN || t > t_max)
		return (false);
	return (true);
}
