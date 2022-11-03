#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

bool	hit_cylinder(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr) 
{
	bool	ret;
	
	ret = false;
	if(hit_cylinder_side(ray, sp, rec, descr) == true)
		ret = true;
	if(hit_cylinder_cap(ray, sp, rec, descr))
		ret = true;
	return (ret);
}


static bool	cylinder_side(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr) 
{
	t_vec3	temp;

	
	vec_minus(&oc, ray.p, sp->p);
	a = vec_dot(ray.dir, ray.dir);
	half_b = vec_dot(oc, ray.dir);
	discriminant = pow(half_b, 2) - (a * (vec_dot(oc, oc) - pow(sp->r, 2)));
	if (discriminant < 0)
		return (false);
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < MIN || root > rec->t_max)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < MIN || root > rec->t_max)
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

// static bool	hit_plane(t_ray ray, t_plane *pl, t_rec *rec, t_descr *descr) 
// {
// 	double	discriminant;
// 	double	d;
// 	double	t;

// 	discriminant = vec_dot(pl->o, ray.dir);
// 	if (discriminant < MIN && -discriminant < MIN)
// 		return (false);
// 	d = vec_dot(pl->o, pl->p);
// 	t = (d - vec_dot(pl->o, ray.p)) / discriminant;
// 	if (t < MIN || t > rec->t_max)
// 			return (false);
// 	rec->t = t;
// 	rec->t_max = t;
// 	ray_at(&rec->p, ray, t);
// 	rec->norm = pl->o;
// 	set_face(ray, rec);
// 	set_color(pl->c, ray, rec, descr);
// 	return (true);
// }