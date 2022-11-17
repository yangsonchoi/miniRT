#include "minirt.h"
#include "utils.h"
#include "parse.h"
#include "libft.h"
#include "mlx.h"
#include "draw.h"
#include <unistd.h>

#define ESC_KEY	53
#define CHANGE	

#include <stdio.h> // test

static void	initial_variables(t_vars *vars, t_img *img, t_descr *descr);
static void	initial_mlx(t_vars *vars, t_img *img);
static int	key_press(int key_input, t_vars *vars, t_descr *descr);

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;
	t_descr	descr;

	if (argc != 2)
		err_exit(NULL, 22);
	initial_variables(&vars, &img, &descr);
	parse_scene(&descr, argv[1]);
	int i;
	{
		printf("ambient count : %d\n\n", descr.cnt.al_cnt);
		printf("color R: %f G: %f B: %f\n\n", descr.al.cr.x, descr.al.cr.y, descr.al.cr.z);
	}	
	{
		printf("camera count : %d\n\n", descr.cnt.c_cnt);
		printf("position x: %f, y: %f, z: %f\n", descr.c.p.x, descr.c.p.y, descr.c.p.z);
		printf("orientation x: %f, y: %f, z: %f\n", -descr.c.o.x, -descr.c.o.y, -descr.c.o.z);
		printf("FOV: %d\n\n", descr.c.fov);
	}	
	{
		printf("light count : %d\n\n", descr.cnt.l_cnt);
		printf("position x: %f, y: %f, z: %f\n", descr.l.p.x, descr.l.p.y, descr.l.p.z);
		printf("color R: %f G: %f B: %f\n\n", descr.l.cb.x, descr.l.cb.y, descr.l.cb.z);
	}		
	i = 0;
	if (descr.sp != NULL)
	{
		printf("sphere count : %d\n\n", descr.cnt.sp_cnt);
		while ((descr.sp)[i] != NULL)
		{
			printf("sphere #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (descr.sp)[i]->p.x, (descr.sp)[i]->p.y, (descr.sp)[i]->p.z);
			printf("radius: %f\n", (descr.sp)[i]->r);
			printf("color R: %f G: %f B: %f\n\n", (descr.sp)[i]->c.x, (descr.sp)[i]->c.y, (descr.sp)[i]->c.z);
			i++;
		}
	}	
	i = 0;
	if (descr.pl != NULL)
	{
		printf("plane count : %d\n\n", descr.cnt.pl_cnt);
		while ((descr.pl)[i] != NULL)
		{
			printf("plane #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (descr.pl)[i]->p.x, (descr.pl)[i]->p.y, (descr.pl)[i]->p.z);
			printf("orientation: x: %f, y: %f, z: %f\n", (descr.pl)[i]->o.x, (descr.pl)[i]->o.y, (descr.pl)[i]->o.z);
			printf("color R: %f G: %f B: %f\n\n", (descr.pl)[i]->c.x, (descr.pl)[i]->c.y, (descr.pl)[i]->c.z);
			i++;
		}
	}
	i = 0;
	if (descr.cy != NULL)
	{
		printf("cylinder count : %d\n\n", descr.cnt.cy_cnt);
		while ((descr.cy)[i] != NULL)
		{
			printf("cylider #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (descr.cy)[i]->p.x, (descr.cy)[i]->p.y, (descr.cy)[i]->p.z);
			printf("orientation: x: %f, y: %f, z: %f\n", (descr.cy)[i]->o.x, (descr.cy)[i]->o.y, (descr.cy)[i]->o.z);
			printf("radius: %f, height, %f\n", (descr.cy)[i]->r, (descr.cy)[i]->h);
			printf("color R: %f G: %f B: %f\n\n", (descr.cy)[i]->c.x, (descr.cy)[i]->c.y, (descr.cy)[i]->c.z);
			i++;
		}
	}
	if (descr.cnt.al_cnt != 1 || descr.cnt.c_cnt != 1 || descr.cnt.l_cnt != 1)
		err_exit_descr(&descr, NULL);
	initial_mlx(&vars, &img);
	draw_img(&img, &descr);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_destroy_image(vars.mlx, img.img);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_loop(vars.mlx);
	free_description(&descr);
	printf("exit\n");
}

static void	initial_variables(t_vars *vars, t_img *img, t_descr *descr)
{
	ft_memset(vars, 0, sizeof(t_vars));
	ft_memset(img, 0, sizeof(t_img));
	ft_memset(descr, 0, sizeof(t_descr));
}

static void	initial_mlx(t_vars *vars, t_img *img)
{
 	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT,"Raytracer");
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, \
				&img->bits_per_pixel, &img->size_len, &img->endian);
}

static int	key_press(int key_input, t_vars *vars, t_img *img, t_descr *descr)
{
	if (key_input == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_description(&descr);
		exit(EXIT_SUCCESS);
	}
	if (key_input == )
	return (0);
}