#include "vector.h"

#include <math.h>

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