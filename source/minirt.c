#include "minirt.h"
#include "utils.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

#include <stdio.h> // test

static void	initial_variables(t_vars *vars, t_img *img, t_descr *descr);

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;
	t_descr	descr;

	if (argc != 2)
		err_exit(NULL, 22);
	initial_variables(&vars, &img, &descr);
	parse_scene(&descr, argv[1]);
	int i = 0;
	while ((descr.cy)[i] != NULL)
	{
		printf("cylider #%d\n", i);
		printf("position x: %f, y: %f, z: %f, d: %f\n", (descr.cy)[i]->p.x, (descr.cy)[i]->p.y, (descr.cy)[i]->p.z, (descr.cy)[i]->d);
		printf("orientation: x: %f, y: %f, z: %f\n", (descr.cy)[i]->o.x, (descr.cy)[i]->o.y, (descr.cy)[i]->o.z);
		printf("radius: %f, height, %f\n", (descr.cy)[i]->r, (descr.cy)[i]->h);
		printf("color R: %d G: %d B: %d\n\n", (descr.cy)[i]->c.trgb[2], (descr.cy)[i]->c.trgb[1], (descr.cy)[i]->c.trgb[0]);
		i++;
	}
}

static void	initial_variables(t_vars *vars, t_img *img, t_descr *descr)
{
	ft_memset(vars, 0, sizeof(t_vars));
	ft_memset(img, 0, sizeof(t_img));
	ft_memset(descr, 0, sizeof(t_descr));
}