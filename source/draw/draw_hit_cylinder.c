/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:53:11 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:53:12 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static bool	hit_cy_side(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr);
static bool	valid_dcr(t_rec *rec, double *root, t_ray ray, t_cylinder *cy);
static bool	hit_cap_up(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr);
static bool	hit_cap_down(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr);

bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr)
{
	bool	ret;

	ret = false;
	if (cy->h < 0 || cy->r < 0)
		return (false);
	if (hit_cy_side(ray, cy, rec, descr) == true)
		ret = true;
	if (hit_cap_up(ray, cy, rec, descr) == true)
		ret = true;
	if (hit_cap_down(ray, cy, rec, descr) == true)
		ret = true;
	return (ret);
}

static bool	hit_cy_side(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr)
{
	t_vec3	oc;
	double	root;
	double	m;

	vec_minus(&oc, ray.p, cy->p);
	if (valid_dcr(rec, &root, ray, cy) == false)
		return (false);
	ray_at(&rec->p, ray, root);
	rec->t = root;
	rec->t_max = root;
	m = (vec_dot(ray.dir, cy->o) * root) + vec_dot(oc, cy->o);
	vec_mul_db(&rec->norm, cy->o, m);
	vec_plus(&rec->norm, cy->p, rec->norm);
	vec_minus(&rec->norm, rec->p, rec->norm);
	vec_convert_unit(rec->norm, &rec->norm);
	set_face(ray, rec);
	set_color(cy->c, rec, descr);
	return (true);
}

static bool	valid_dcr(t_rec *rec, double *rt, t_ray ray, t_cylinder *cy)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	dcr;
	double	m;

	vec_minus(&oc, ray.p, cy->p);
	a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, cy->o), 2);
	half_b = vec_dot(ray.dir, oc)
		- (vec_dot(ray.dir, cy->o) * vec_dot(oc, cy->o));
	dcr = pow(half_b, 2)
		- (a * (vec_dot(oc, oc) - pow(vec_dot(oc, cy->o), 2) - pow(cy->r, 2)));
	if (dcr < 0)
		return (false);
	*rt = ((half_b * -1) - sqrt(dcr)) / a;
	m = (vec_dot(ray.dir, cy->o) * (*rt)) + vec_dot(oc, cy->o);
	if (*rt < MIN || *rt > rec->t_max || m > cy->h / 2 || m < cy->h / 2 * -1)
	{
		*rt = ((half_b * -1) + sqrt(dcr)) / a;
		m = (vec_dot(ray.dir, cy->o) * (*rt)) + vec_dot(oc, cy->o);
		if (*rt < MIN || *rt > rec->t_max
			|| m > cy->h / 2 || m < cy->h / 2 * -1)
			return (false);
	}
	return (true);
}

static bool	hit_cap_up(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr)
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
	if (t < MIN || t > rec->t_max)
		return (false);
	ray_at(&p, ray, t);
	vec_minus(&center, p, center);
	if (sqrt(vec_dot(center, center)) > cy->r)
		return (false);
	rec->t = t;
	rec->t_max = t;
	ray_at(&rec->p, ray, t);
	rec->norm = cy->o;
	set_face(ray, rec);
	set_color(cy->c, rec, descr);
	return (true);
}

static bool	hit_cap_down(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr)
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
	if (t < MIN || t > rec->t_max)
		return (false);
	ray_at(&p, ray, t);
	vec_minus(&center, p, center);
	if (sqrt(vec_dot(center, center)) > cy->r)
		return (false);
	rec->t = t;
	rec->t_max = t;
	ray_at(&rec->p, ray, t);
	vec_mul_db(&rec->norm, cy->o, -1);
	set_face(ray, rec);
	set_color(cy->c, rec, descr);
	return (true);
}
