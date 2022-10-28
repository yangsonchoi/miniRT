#include "draw.h"
#include "minirt.h"
#include "vector.h"

#include <math.h>

#include <stdio.h> // test

static void	set_viewport(t_draw *draw, t_descr *descr);
static t_color	shoot_ray(t_draw draw, t_descr *descr);
static void	draw_pixel(t_color color, t_draw draw, t_img *img);


void	draw_img(t_img *img, t_descr *descr)
{
	t_color	ray_color;
	t_draw	draw;

	set_viewport(&draw, descr);
	draw.h = HEIGHT - 1;
	while (draw.h > -1)
	{
		draw.w = 0;
		while (draw.w < WIDTH)
		{
			ray_color = shoot_ray(draw, descr);
			draw_pixel (ray_color, draw, img);
			draw.w++;
		}
		draw.h--;
	}
}

static void	set_viewport(t_draw *draw, t_descr *descr)
{
	double	fov_rad;
	t_vec3	temp;

	fov_rad = M_PI * descr->c.fov / 2 / 180;
	draw->cam_h.x = tan(fov_rad) * 2;
	draw->cam_h.y = 0;
	draw->cam_h.z = 0;
	draw->cam_v.x = tan(fov_rad) * 2 * HEIGHT / WIDTH;
	draw->cam_v.y = 0;
	draw->cam_v.z = 0;
	vec_mul_db(&draw->llc, descr->c.p, descr->c.d);
	vec_div_db(&temp, draw->cam_h, 2);
	vec_minus(&draw->llc, draw->llc, temp);
	vec_div_db(&temp, draw->cam_v, 2);
	vec_minus(&draw->llc, draw->llc, temp);
	temp.x = 0;
	temp.y = 0;
	temp.z = 1;
	vec_minus(&draw->llc, draw->llc, temp);
}

static t_color	shoot_ray(t_draw draw, t_descr *descr)
{
	t_color	ret;
	t_ray	ray;
	t_vec3	temp;
	double	t;

	ray.p = descr->c.p;
	ray.d = descr->c.d;
	ray.dir.x = draw.llc.x + (((double)(draw.w) / (WIDTH - 1)) * draw.cam_h.x) + (((double)(draw.h) / (HEIGHT - 1)) * draw.cam_v.x) - descr->c.p.x;
	ray.dir.y = draw.llc.y + (((double)(draw.w) / (WIDTH - 1)) * draw.cam_h.y) + (((double)(draw.h) / (HEIGHT - 1)) * draw.cam_v.y) - descr->c.p.y;
	ray.dir.z = draw.llc.z + (((double)(draw.w) / (WIDTH - 1)) * draw.cam_h.z) + (((double)(draw.h) / (HEIGHT - 1)) * draw.cam_v.z) - descr->c.p.z;
	vec_convert_unit(ray.dir, &temp);
	t = 0.5 * (temp.y + 1);
	printf("t : %f.2  ", t);
	ret.trgb[3] = 0;
	ret.trgb[2] = (1.0 - t) * 255.99 + t * 255.99 * 0.5;
	ret.trgb[1] = (1.0 - t) * 255.99 + t * 255.99 * 0.7;
	ret.trgb[0] = (1.0 - t) * 255.99 + t * 255.99 * 1.0;
	return (ret);
}

static void	draw_pixel(t_color color, t_draw draw, t_img *img)
{
	char	*dst;

	dst = img->addr + (draw.h * img->size_len + (draw.w * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color.color;
}