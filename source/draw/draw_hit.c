#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static bool	hit_sphere(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr);

bool	hit_object(t_ray ray, t_rec *rec, t_descr *descr)
{
	int	hit;
	int	i;

	hit = 0;;
	i = 0;
	rec->t_max = T_MAX;
	if (descr->sp != NULL)
	{
		while (descr->sp[i] != NULL)
			hit += hit_sphere(ray, descr->sp[i++], rec, descr);
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
	if (discriminant < 0)
		return (false);
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < T_MIN || root > rec->t_max)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < T_MIN || root > rec->t_max)
			return (false);
	}
	rec->t = root;
	rec->t_max = root;
	ray_at(&rec->p, ray, root);
	vec_minus(&rec->norm, rec->p, sp->p);
	vec_convert_unit(rec->norm, &rec->norm);
	set_face(ray, rec);
	set_color(sp->c, ray, rec, descr);
	return (true);
}

