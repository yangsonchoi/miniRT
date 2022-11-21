/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:05:43 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 13:05:44 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

#include <stdio.h> // test

static void		set_viewport(t_draw *draw, t_descr *descr);
static t_color	shoot_ray(t_draw draw, t_descr *descr);
static void		draw_pixel(t_color color, t_draw draw, t_img *img);

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
	t_vec3	u;
	t_vec3	v;

	fov_rad = M_PI * descr->c.fov / 2 / 180;
	vec_cross(&temp, vec_set(0, 1, 0), descr->c.o);
	vec_convert_unit(temp, &u);
	vec_mul_db(&draw->cam_h, u, tan(fov_rad) * 2);
	vec_cross(&v, descr->c.o, u);
	vec_mul_db(&draw->cam_v, v, tan(fov_rad) * 2 * HEIGHT / WIDTH);
	draw->llc = descr->c.p;
	vec_div_db(&temp, draw->cam_h, 2);
	vec_minus(&draw->llc, descr->c.p, temp);
	vec_div_db(&temp, draw->cam_v, 2);
	vec_minus(&draw->llc, draw->llc, temp);
	vec_convert_unit(descr->c.o, &temp);
	vec_minus(&draw->llc, draw->llc, temp);
}

static t_color	shoot_ray(t_draw draw, t_descr *descr)
{
	t_color	ret;
	t_ray	ray;
	t_vec3	temp;
	double	t;
	t_rec	rec;

	draw.h = HEIGHT - 1 - draw.h;
	ray.p = descr->c.p;
	set_ray_dir(&ray, draw, descr);
	if (hit_object(ray, &rec, descr) == true)
	{	
		ret = color_set(rec.c.x, rec.c.y, rec.c.z);
		return (ret);
	}
	vec_convert_unit(ray.dir, &temp);
	t = 0.5 * (temp.y + 1);
	ret.trgb[3] = 0;
	ret.trgb[2] = (1.0 - t) * 255.99 + t * 255.99 * 0.5;
	ret.trgb[1] = (1.0 - t) * 255.99 + t * 255.99 * 0.7;
	ret.trgb[0] = (1.0 - t) * 255.99 + t * 255.99 * 1.0;
	return (ret);
}

static void	set_ray_dir(t_ray *ray, t_draw draw, t_descr *descr)
{
	ray->dir.x = draw.llc.x + (((double)(draw.w) / (double)(WIDTH - 1))
			* draw.cam_h.x) + (((double)(draw.h) / (double)(HEIGHT - 1))
			* draw.cam_v.x) - descr->c.p.x;
	ray->dir.y = draw.llc.y + (((double)(draw.w) / (double)(WIDTH - 1))
			* draw.cam_h.y) + (((double)(draw.h) / (double)(HEIGHT - 1))
			* draw.cam_v.y) - descr->c.p.y;
	ray->dir.z = draw.llc.z + (((double)(draw.w) / (double)(WIDTH - 1))
			* draw.cam_h.z) + (((double)(draw.h) / (double)(HEIGHT - 1))
			* draw.cam_v.z) - descr->c.p.z;
}

static void	draw_pixel(t_color color, t_draw draw, t_img *img)
{
	char	*dst;

	dst = img->addr
		+ (draw.h * img->size_len + (draw.w * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color.color;
}
