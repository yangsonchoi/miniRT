#include "minirt.h"
#include "utils.h"
#include "parse.h"
#include "libft.h"
#include "mlx.h"
#include "draw.h"
#include <unistd.h>

#define ESC_KEY 53

#include <stdio.h> // test

static void	initial_variables(t_vars *vars, t_img *img, t_descr *descr);
static void	initial_mlx(t_vars *vars, t_img *img);
static int	terminate(int key_input, t_vars *vars);

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
		printf("brightness: %f\n", descr.al.r);
		printf("color R: %d G: %d B: %d\n\n", descr.al.c.trgb[2], descr.al.c.trgb[1], descr.al.c.trgb[0]);
	}	
	{
		printf("camera count : %d\n\n", descr.cnt.c_cnt);
		printf("position x: %f, y: %f, z: %f\n", descr.c.p.x, descr.c.p.y, descr.c.p.z);
		printf("orientation x: %f, y: %f, z: %f\n", descr.c.o.x, descr.c.o.y, descr.c.o.z);
		printf("FOV: %d\n\n", descr.c.fov);
	}	
	{
		printf("light count : %d\n\n", descr.cnt.l_cnt);
		printf("position x: %f, y: %f, z: %f\n", descr.l.p.x, descr.l.p.y, descr.l.p.z);
		printf("brightness: %f\n", descr.l.b);
		printf("color R: %d G: %d B: %d\n\n", descr.l.c.trgb[2], descr.l.c.trgb[1], descr.l.c.trgb[0]);
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
			printf("color R: %d G: %d B: %d\n\n", (descr.sp)[i]->c.trgb[2], (descr.sp)[i]->c.trgb[1], (descr.sp)[i]->c.trgb[0]);
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
			printf("color R: %d G: %d B: %d\n\n", (descr.pl)[i]->c.trgb[2], (descr.pl)[i]->c.trgb[1], (descr.pl)[i]->c.trgb[0]);
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
			printf("color R: %d G: %d B: %d\n\n", (descr.cy)[i]->c.trgb[2], (descr.cy)[i]->c.trgb[1], (descr.cy)[i]->c.trgb[0]);
			i++;
		}
	}
	if (descr.cnt.al_cnt != 1 || descr.cnt.c_cnt != 1 || descr.cnt.l_cnt != 1)
		err_exit_descr(&descr, NULL);
	initial_mlx(&vars, &img);
	draw_img(&img, &descr);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_destroy_image(vars.mlx, img.img);
	mlx_key_hook(vars.win, terminate, &vars);
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

static int	terminate(int key_input, t_vars *vars)
{
	if (key_input == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}