#include "parse.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"

#include <stdbool.h>

static enum e_des_type	des_type(char *parse);

void	parse_description(char *input, t_descr *descr)
{
	char			**des;
	enum e_des_type	type;

	des = ft_split(ft_strtrim(input, "\n"), ' ');
	if (des != NULL)
	{
		type = des_type(des[0]);
		// if (type == AMBIENT_LIGHT)
		// 	parse_al(des, descr);
		// else if (type == CAMERA)
		// 	parse_c(des, descr);
		// else if (type == LIGHT)
		// 	parse_l(des, descr);
		// else if (type == SPHERE)
		// 	parse_sp(des, descr);
		// else if (type == PLANE)
		// 	parse_pl(des, descr);
		if (type == CYLINDER)
			parse_cy(des, descr);
		else if (type == ELSE)
			err_exit_descr(descr, des);
		free_dcharp(des);
	}
}

static enum e_des_type	des_type(char *parse)
{
	int	len;
	
	len = ft_strlen(parse);
	if (ft_strncmp(parse, "A", len) == 0)
		return (AMBIENT_LIGHT);
	else if (ft_strncmp(parse, "C", len) == 0)
		return (CAMERA);
	else if (ft_strncmp(parse, "L", len) == 0)
		return (LIGHT);
	else if (ft_strncmp(parse, "sp", len) == 0)
		return (SPHERE);
	else if (ft_strncmp(parse, "pl", len) == 0)
		return (PLANE);
	else if (ft_strncmp(parse, "cy", len) == 0)
		return (CYLINDER);
	else
		return (ELSE);
}