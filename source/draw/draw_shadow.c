#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static double set_shadow_ray(t_ray *ray, t_rec rec, t_descr *descr);
static bool	hit_sphere_shadow(t_ray ray, t_sphere *sp, double t_min);

bool	hit_object_shadow(t_rec rec, t_descr *descr)
{
	int	i;
	t_ray	ray;
	double	t_min;

	i = 0;
	t_min = set_shadow_ray(&ray, rec, descr);
	if (descr->sp != NULL)
	{
		while (descr->sp[i] != NULL)
			if(hit_sphere_shadow(ray, descr->sp[i++], t_min) == true)
				return (true);
	}
	// if (descr->sp != NULL)
	// {
	// 	while (descr->sp[i] != NULL)
	// 		if(hit_sphere_shadow(ray, descr->sp[i++], rec, descr) == true)
	// 			return (true);
	// }
	// if (descr->sp != NULL)
	// {
	// 	while (descr->sp[i] != NULL)
	// 		if(hit_sphere_shadow(ray, descr->sp[i++], rec, descr) == true)
	// 			return (true);
	// }
	return (false);
}

static double set_shadow_ray(t_ray *ray, t_rec rec, t_descr *descr)
{
	double	light_len;

	ray->p = rec.p;
	vec_minus(&ray->dir, descr->l.p, ray->p);
	light_len = sqrt(vec_dot(ray->dir, ray->dir));
	vec_convert_unit(ray->dir, &ray->dir);
	return(light_len);
}

static bool	hit_sphere_shadow(t_ray ray, t_sphere *sp, double t_min) 
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
	if (root < t_min || root > T_MAX)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < t_min|| root > T_MAX)
			return (false);
	}
	return (true);
}