#include "minirt.h"
#include <unistd.h>

static void	initial_varialbes(t_vars *vars, t_img *img, t_descr *descr);

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;
	t_descr	descr;

	if (argc != 2)
		err_exit(NULL, 22);
	initial_variables(&vars, &img, &descr);
	parse_scene(&descr, argv[1]);
}

static void	initial_varialbes(t_vars *vars, t_img *img, t_descr *descr)
{
	ft_memset(vars, 0, sizeof(t_vars));
	ft_memset(img, 0, sizeof(t_img));
	ft_memset(descr, 0, sizeof(t_descr));
}