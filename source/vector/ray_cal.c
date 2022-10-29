#include "vector.h"
#include "draw.h"

#include <math.h>
#include <stdbool.h>

void	ray_at(t_vec3 *dest, t_ray a, double b)
{
	t_vec3	temp;

	vec_mul_db(&temp, a.dir, b);
	vec_plus(dest, a.p, temp);
}

void	set_face(t_ray ray, t_rec *rec)
{
	rec->face = vec_dot(ray.dir, rec->norm) < 0;
	if (rec->face == false)
		vec_mul_db(&rec->norm, rec->norm, -1);
}