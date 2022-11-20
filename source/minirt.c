#include "minirt.h"
#include "utils.h"
#include "parse.h"
#include "libft.h"
#include "mlx.h"
#include "draw.h"
#include "edit.h"

#include <unistd.h>
#include <stdbool.h>

#include <stdio.h> // test
#include "vector.h"

static void	initial_mlx(t_vars *vars, t_img *img);
static void	draw_loop(t_vars *vars, t_img *img, t_descr *descr);
static int	key_press(int key_input, t_vars *vars);

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		err_exit(NULL, 22);
	ft_memset(&vars, 0, sizeof(t_vars));
	parse_scene(&vars.descr, argv[1]);
	int i;
	{
		printf("ambient count : %d\n\n", vars.descr.cnt.al_cnt);
		printf("color R: %f G: %f B: %f\n\n", vars.descr.al.cr.x, vars.descr.al.cr.y, vars.descr.al.cr.z);
	}	
	{
		printf("camera count : %d\n\n", vars.descr.cnt.c_cnt);
		printf("position x: %f, y: %f, z: %f\n", vars.descr.c.p.x, vars.descr.c.p.y, vars.descr.c.p.z);
		printf("orientation x: %f, y: %f, z: %f\n", -vars.descr.c.o.x, -vars.descr.c.o.y, -vars.descr.c.o.z);
		printf("FOV: %d\n\n", vars.descr.c.fov);
	}	
	{
		printf("light count : %d\n\n", vars.descr.cnt.l_cnt);
		printf("position x: %f, y: %f, z: %f\n", vars.descr.l.p.x, vars.descr.l.p.y, vars.descr.l.p.z);
		printf("color R: %f G: %f B: %f\n\n", vars.descr.l.cb.x, vars.descr.l.cb.y, vars.descr.l.cb.z);
	}		
	i = 0;
	if (vars.descr.sp != NULL)
	{
		printf("sphere count : %d\n\n", vars.descr.cnt.sp_cnt);
		while ((vars.descr.sp)[i] != NULL)
		{
			printf("sphere #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (vars.descr.sp)[i]->p.x, (vars.descr.sp)[i]->p.y, (vars.descr.sp)[i]->p.z);
			printf("radius: %f\n", (vars.descr.sp)[i]->r);
			printf("color R: %f G: %f B: %f\n\n", (vars.descr.sp)[i]->c.x, (vars.descr.sp)[i]->c.y, (vars.descr.sp)[i]->c.z);
			i++;
		}
	}	
	i = 0;
	if (vars.descr.pl != NULL)
	{
		printf("plane count : %d\n\n", vars.descr.cnt.pl_cnt);
		while ((vars.descr.pl)[i] != NULL)
		{
			printf("plane #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (vars.descr.pl)[i]->p.x, (vars.descr.pl)[i]->p.y, (vars.descr.pl)[i]->p.z);
			printf("orientation: x: %f, y: %f, z: %f\n", (vars.descr.pl)[i]->o.x, (vars.descr.pl)[i]->o.y, (vars.descr.pl)[i]->o.z);
			printf("color R: %f G: %f B: %f\n\n", (vars.descr.pl)[i]->c.x, (vars.descr.pl)[i]->c.y, (vars.descr.pl)[i]->c.z);
			i++;
		}
	}
	i = 0;
	if (vars.descr.cy != NULL)
	{
		printf("cylinder count : %d\n\n", vars.descr.cnt.cy_cnt);
		while ((vars.descr.cy)[i] != NULL)
		{
			printf("cylider #%d\n", i);
			printf("position x: %f, y: %f, z: %f\n", (vars.descr.cy)[i]->p.x, (vars.descr.cy)[i]->p.y, (vars.descr.cy)[i]->p.z);
			printf("orientation: x: %f, y: %f, z: %f\n", (vars.descr.cy)[i]->o.x, (vars.descr.cy)[i]->o.y, (vars.descr.cy)[i]->o.z);
			printf("radius: %f, height, %f\n", (vars.descr.cy)[i]->r, (vars.descr.cy)[i]->h);
			printf("color R: %f G: %f B: %f\n\n", (vars.descr.cy)[i]->c.x, (vars.descr.cy)[i]->c.y, (vars.descr.cy)[i]->c.z);
			i++;
		}
	}
	if (vars.descr.cnt.al_cnt != 1 || vars.descr.cnt.c_cnt != 1 || vars.descr.cnt.l_cnt != 1)
		err_exit_descr(&vars.descr, NULL);
	initial_mlx(&vars, &vars.img);
	draw_loop(&vars, &vars.img, &vars.descr);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_loop(vars.mlx);
	free_description(&vars.descr);
}

static void	initial_mlx(t_vars *vars, t_img *img)
{
 	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT,"Raytracer");
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, \
				&img->bits_per_pixel, &img->size_len, &img->endian);
}

static void	draw_loop(t_vars *vars, t_img *img, t_descr *descr)
{
	draw_img(img, descr);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

static int	key_press(int key_input, t_vars *vars)
{
	if (key_input == KEY_ESC)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		free_description(&vars->descr);
		exit(EXIT_SUCCESS);
	}
	else if (vars->edit.stat == false && key_input == KEY_E)
		edit_on(vars);
	else if (vars->edit.stat == true && key_input == KEY_ENTER)
		edit_off(vars);
	else if (vars->edit.stat == true)
	{
		if (edit_mode(key_input, vars) == true)
			draw_loop(vars, &vars->img, &vars->descr);
	}
	return (0);
}
