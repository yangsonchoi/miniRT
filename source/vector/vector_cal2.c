#include "vector.h"

#include <math.h>

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

void	vec_cross(t_vec3 *dest, t_vec3 a, t_vec3 b)
{
	dest->x = (a.y * b.z) - (a.z * b.y);
	dest->y = (a.z * b.x) - (a.x * b.z);
	dest->z = (a.x * b.y) - (a.y * b.x);
}

double	vec_convert_unit(t_vec3 input, t_vec3 *dest)
{
	double	d;

	d = sqrt(pow(input.x, 2) + pow(input.y, 2) + pow(input.z, 2));
	if (d == 0.0)
	{
		dest->x = 0.0;
		dest->y = 0.0;
		dest->z = 0.0;
	}
	else
	{
		dest->x = input.x / d;
		dest->y = input.y / d;
		dest->z = input.z / d;
	}
	return (d);
}

t_vec3	vec_set(double x, double y, double z)
{
	t_vec3	ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_color	color_set(double x, double y, double z)
{
	t_color	ret;
	ret.trgb[3] = 0;
	ret.trgb[2] = x;
	ret.trgb[1] = y;
	ret.trgb[0] = z;
	return (ret);
}