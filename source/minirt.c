/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:31:57 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:31:59 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "utils.h"
#include "parse.h"
#include "libft.h"
#include "mlx.h"
#include "draw.h"
#include "edit.h"
#include "vector.h"

#include <unistd.h>
#include <stdbool.h>

static void	initial_mlx(t_vars *vars, t_img *img);
static void	draw_loop(t_vars *vars, t_img *img, t_descr *descr);
static void	key_press(int key_input, t_vars *vars);

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		err_exit(NULL, 22);
	ft_memset(&vars, 0, sizeof(t_vars));
	parse_scene(&vars.descr, argv[1]);
	if (vars.descr.cnt.al_cnt != 1 || vars.descr.cnt.c_cnt != 1
		|| vars.descr.cnt.l_cnt != 1)
		err_exit_descr(&vars.descr, NULL);
	initial_mlx(&vars, &vars.img);
	draw_loop(&vars, &vars.img, &vars.descr);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, 17, 1L << 17, win_destroy, &vars);
	mlx_loop(vars.mlx);
	free_description(&vars.descr);
}

static void	initial_mlx(t_vars *vars, t_img *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Raytracer");
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, \
				&img->bits_per_pixel, &img->size_len, &img->endian);
}

static void	draw_loop(t_vars *vars, t_img *img, t_descr *descr)
{
	draw_img(img, descr);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

static void	key_press(int key_input, t_vars *vars)
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
}

static void	win_destroy(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	free_description(&vars->descr);
	exit(EXIT_SUCCESS);
}