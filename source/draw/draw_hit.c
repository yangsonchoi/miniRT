/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:33:20 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:33:22 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static bool	hit_sphere(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr);
static void	set_rec(double root, t_rec *rec, t_ray ray, t_sphere *sp);
static bool	hit_plane(t_ray ray, t_plane *pl, t_rec *rec, t_descr *descr);

bool	hit_object(t_ray ray, t_rec *rec, t_descr *descr)
{
	int	hit;
	int	i;

	hit = 0;
	i = 0;
	rec->t_max = MAX;
	if (descr->sp != NULL)
	{
		while (descr->sp[i] != NULL)
			hit += hit_sphere(ray, descr->sp[i++], rec, descr);
	}
	i = 0;
	if (descr->pl != NULL)
	{
		while (descr->pl[i] != NULL)
			hit += hit_plane(ray, descr->pl[i++], rec, descr);
	}
	i = 0;
	if (descr->cy != NULL)
	{
		while (descr->cy[i] != NULL)
			hit += hit_cylinder(ray, descr->cy[i++], rec, descr);
	}
	return (hit);
}

static bool	hit_sphere(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr)
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
	if (discriminant < 0 || sp->r < 0)
		return (false);
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < MIN || root > rec->t_max)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < MIN || root > rec->t_max)
			return (false);
	}
	set_rec(root, rec, ray, sp);
	set_color(sp->c, rec, descr);
	return (true);
}

static void	set_rec(double root, t_rec *rec, t_ray ray, t_sphere *sp)
{
	rec->t = root;
	rec->t_max = root;
	ray_at(&rec->p, ray, root);
	vec_minus(&rec->norm, rec->p, sp->p);
	vec_convert_unit(rec->norm, &rec->norm);
	set_face(ray, rec);
}

static bool	hit_plane(t_ray ray, t_plane *pl, t_rec *rec, t_descr *descr)
{
	double	discriminant;
	double	d;
	double	t;

	discriminant = vec_dot(pl->o, ray.dir);
	if (discriminant < MIN && -1 * discriminant < MIN)
		return (false);
	d = vec_dot(pl->o, pl->p);
	t = (d - vec_dot(pl->o, ray.p)) / discriminant;
	if (t < MIN || t > rec->t_max)
		return (false);
	rec->t = t;
	rec->t_max = t;
	ray_at(&rec->p, ray, t);
	rec->norm = pl->o;
	set_face(ray, rec);
	set_color(pl->c, rec, descr);
	return (true);
}
