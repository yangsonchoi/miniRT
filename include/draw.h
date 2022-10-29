#ifndef	DRAW_H
# define DRAW_H

# include "minirt.h"
# include <math.h>
# include <stdbool.h>

# define T_MIN 0.0
# define T_MAX INFINITY

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
	t_vec3	dir;

}	t_ray;

typedef struct s_rec
{
	t_vec3	p;
	t_vec3	norm;
	double	t;
	bool	face;
}	t_rec;


/*
** draw.c
*/
void	draw_img(t_img *img, t_descr *descr);

#endif