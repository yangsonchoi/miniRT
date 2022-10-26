#include "parse.h"
#include "utils.h"
#include "libft.h"
#include "vector.h"

#include <stdbool.h>

double	convert_double(char *input)
{
	double	front;
	double	back;
	int		len;
	char	*temp;

	front = ft_atoi(input);
	temp = ft_strchr(input, '.');
	len = ft_strlen(&temp[1]);
	back = ft_atoi(&temp[1]);
	while (len > 0)
	{
		back /= 10;
		len--;
	}
	if (front < 0)
		return (front - back);
	else
		return (front + back);
}

bool	convert_vec3(char *input, t_vec3 *vec, double *len, bool check)
{
	char	**temp;
	t_vec3	temp_vec;

	temp = ft_split(input, ',');
	temp_vec.x = convert_double(temp[0]);
	temp_vec.y = convert_double(temp[1]);
	temp_vec.z = convert_double(temp[2]);
	free_dcharp(temp);
	if (check == true)
	{
		if (temp_vec.x > 1.0 || temp_vec.x < -1.0 || 
			temp_vec.y > 1.0 || temp_vec.y < -1.0 ||
			temp_vec.z > 1.0 || temp_vec.z < -1.0 )
			return (false);
	}
	if (len != NULL)
		*len = vec_convert_unit(temp_vec, vec);
	else
		vec_convert_unit(temp_vec, vec);
	return (true);
}

bool	convert_rgb(char *input, t_color *dest)
{
	char	*temp;
	int		temp_int;

	temp_int = atoi(input);
	if (temp_int < 0 || temp_int > 255)
		return (false);
	(dest->trgb)[2] = (unsigned char)temp_int;
	temp = ft_strchr(input, ',');
	temp_int = atoi(&temp[1]);
	if (temp_int < 0 || temp_int > 255)
		return (false);
	(dest->trgb)[1] = (unsigned char)temp_int;
	temp = ft_strchr(&temp[1], ',');
		temp_int = atoi(&temp[1]);
	if (temp_int < 0 || temp_int > 255)
		return (false);
	(dest->trgb)[0] = (unsigned char)temp_int;
	return (true);
}