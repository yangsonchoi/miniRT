#ifndef	DRAW_H
# define DRAW_H

# include "minirt.h"
# include <math.h>
# include <stdbool.h>

# define MIN 1e-6
# define MAX INFINITY

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
	double	t_max;
	t_vec3	c;
	bool	face;
}	t_rec;


/*
** draw.c
*/
void	draw_img(t_img *img, t_descr *descr);

/*
** draw_hit.c
*/
bool	hit_object(t_ray ray, t_rec *rec, t_descr *descr);

/*
** draw_hit_cylinder.c
*/
bool	hit_cylinder(t_ray ray, t_cylinder *cy, t_rec *rec, t_descr *descr);

/*
** draw_light.c
*/
void	set_color(t_vec3 obj, t_ray ray, t_rec *rec, t_descr *descr);

/*
** draw_shadow.c
*/
bool	hit_object_shadow(t_rec rec, t_descr *descr);

/*
** draw_shadow_cylinder.c
*/
bool	cylinder_shadow(t_ray ray, t_descr *descr, 	double	t_max);

#endif