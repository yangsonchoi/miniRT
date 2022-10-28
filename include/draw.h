#ifndef	DRAW_H
# define DRAW_H

#include "minirt.h"

typedef	struct s_draw
{
	t_vec3	cam_h;
	t_vec3	cam_v;
	t_vec3	llc;
	int		h;
	int		w;
}	t_draw;

typedef	struct	s_ray
{
	t_vec3	p;
	double	d;
	t_vec3	dir;
}	t_ray;

/*
** draw.c
*/
void	draw_img(t_img *img, t_descr *descr);

#endif