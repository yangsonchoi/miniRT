/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shadow_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:00:14 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:00:16 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static bool	hit_cy_side_sh(t_ray ray, t_cylinder *cy, double t_max, t_vec3 oc);
static bool	hit_cy_cap_up_shadow(t_ray ray, t_cylinder *cy, double t_max);
static bool	hit_cy_cap_down_shadow(t_ray ray, t_cylinder *cy, double t_max);

bool	cylinder_shadow(t_ray ray, t_descr *descr, double t_max)
{	
	int		i;
	t_vec3	oc;

	i = 0;
	while (descr->cy[i] != NULL)
	{
		vec_minus(&oc, ray.p, descr->cy[i]->p);
		if (hit_cy_side_shadow(ray, descr->cy[i], t_max, oc) == true)
			return (true);
		if (hit_cy_cap_up_shadow(ray, descr->cy[i], t_max) == true)
			return (true);
		if (hit_cy_cap_down_shadow(ray, descr->cy[i], t_max) == true)
			return (true);
		i++;
	}
	return (false);
}

static bool	hit_cy_side_sh(t_ray ray, t_cylinder *cy, double t_max, t_vec3 oc)
{
	double	a;
	double	half_b;
	double	dcr;
	double	m;
	double	root;

	a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, cy->o), 2);
	half_b = vec_dot(ray.dir, oc)
		- (vec_dot(ray.dir, cy->o) * vec_dot(oc, cy->o));
	dcr = pow(half_b, 2)
		- (a * (vec_dot(oc, oc) - pow(vec_dot(oc, cy->o), 2) - pow(cy->r, 2)));
	if (dcr < 0)
		return (false);
	root = ((half_b * -1) - sqrt(dcr)) / a;
	m = (vec_dot(ray.dir, cy->o) * (root)) + vec_dot(oc, cy->o);
	if (root < MIN || root > t_max || m > cy->h / 2 || m < cy->h / 2 * -1)
	{
		root = ((half_b * -1) + sqrt(dcr)) / a;
		m = (vec_dot(ray.dir, cy->o) * (root)) + vec_dot(oc, cy->o);
		if (root < MIN || root > t_max || m > cy->h / 2 || m < cy->h / 2 * -1)
			return (false);
	}
	return (true);
}

static bool	hit_cy_cap_up_shadow(t_ray ray, t_cylinder *cy, double t_max)
{
	double	dcr;
	double	t;
	t_vec3	center;
	t_vec3	p;

	dcr = vec_dot(cy->o, ray.dir);
	if (dcr < MIN && -1 * dcr < MIN)
		return (false);
	vec_mul_db(&center, cy->o, cy->h / 2);
	vec_plus(&center, center, cy->p);
	t = (vec_dot(cy->o, center) - vec_dot(cy->o, ray.p)) / dcr;
	if (t < MIN || t > t_max)
		return (false);
	ray_at(&p, ray, t);
	vec_minus(&center, p, center);
	if (sqrt(vec_dot(center, center)) > cy->r)
		return (false);
	return (true);
}

static bool	hit_cy_cap_down_shadow(t_ray ray, t_cylinder *cy, double t_max)
{
	double	dcr;
	double	t;
	t_vec3	center;
	t_vec3	p;

	dcr = vec_dot(cy->o, ray.dir);
	if (dcr < MIN && -1 * dcr < MIN)
		return (false);
	vec_mul_db(&center, cy->o, cy->h / -2);
	vec_plus(&center, center, cy->p);
	t = (vec_dot(cy->o, center) - vec_dot(cy->o, ray.p)) / dcr;
	if (t < MIN || t > t_max)
		return (false);
	ray_at(&p, ray, t);
	vec_minus(&center, p, center);
	if (sqrt(vec_dot(center, center)) > cy->r)
		return (false);
	return (true);
}
