#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static t_vec3	diffuse_light(t_ray ray, t_rec *rec, t_descr *descr);

void	set_color(t_vec3 obj, t_ray ray, t_rec *rec, t_descr *descr)
{
	t_vec3	light;

	light = vec_set(0, 0, 0);
	if (hit_object_shadow(*rec, descr) == false)
	{
		if (descr->cnt.l_cnt != 0)
			vec_plus(&light, light, diffuse_light(ray, rec, descr));
	}
	if (descr->cnt.al_cnt != 0)
		vec_plus(&light, light, descr->al.cr);
	vec_mul_vec(&rec->c, obj, light);
	max_color(&rec->c, rec->c);
}

static t_vec3	diffuse_light(t_ray ray, t_rec *rec, t_descr *descr)
{
	t_vec3	light_dir;
	double	kd;
	t_vec3	diff_light;

	vec_minus(&light_dir, descr->l.p, rec->p);
	vec_convert_unit(light_dir, &light_dir);
	kd = fmax(vec_dot(rec->norm, light_dir), 0.0);
	vec_mul_db(&diff_light, descr->l.cb, kd);
	
	t_vec3	specular;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	temp;
	double	spec;
	double	ksn;
	double	ks;

    vec_mul_db(&view_dir, ray.dir, -1);
	vec_convert_unit(view_dir, &view_dir);
	vec_mul_db(&reflect_dir, light_dir, -1);
	temp = vec_dot(reflect_dir, rec->norm);
	vec_mul_db(&specular, rec->norm, temp * 2);
	vec_minus(&reflect_dir, reflect_dir, specular);
    ksn = 100; // shininess value
    ks = 0.7; // specular strength
    spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
    vec_mul_db(&specular, descr->l.cb, ks *spec);
	vec_plus(&diff_light, diff_light, specular);
	return (diff_light);
}
