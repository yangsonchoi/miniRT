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
static bool		hit_sphere(t_ray ray, t_sphere sp, t_rec *rec);

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
	draw->cam_v.x = 0;
	draw->cam_v.y = tan(fov_rad) * 2 * HEIGHT / WIDTH;
	draw->cam_v.z = 0;
	printf("llc x: %f, y: %f, z: %f\n", draw->llc.x, draw->llc.y, draw->llc.z);
	vec_div_db(&temp, draw->cam_h, 2);
	vec_minus(&draw->llc, descr->c.p, temp);
 	printf("llc x: %f, y: %f, z: %f\n", draw->llc.x, draw->llc.y, draw->llc.z);
	vec_div_db(&temp, draw->cam_v, 2);
	vec_minus(&draw->llc, draw->llc, temp);
	printf("llc x: %f, y: %f, z: %f\n", draw->llc.x, draw->llc.y, draw->llc.z);
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
	t_rec	rec;

	draw.h = HEIGHT - 1 - draw.h;
	ray.p = descr->c.p;
	ray.dir.x = draw.llc.x + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.x) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.x) - descr->c.p.x;
	ray.dir.y = draw.llc.y + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.y) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.y) - descr->c.p.y;
	ray.dir.z = draw.llc.z + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.z) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.z) - descr->c.p.z;
	if (hit_sphere(ray, *descr->sp[0], &rec) == true)
	{	
		ret = color_set(0.5 * (rec.norm.x + 1) * 255, 0.5 * (rec.norm.y + 1) * 255, 0.5 * (rec.norm.z + 1) * 255);
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

static void	draw_pixel(t_color color, t_draw draw, t_img *img)
{
	char	*dst;

	dst = img->addr + (draw.h * img->size_len + (draw.w * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color.color;
}

static bool	hit_sphere(t_ray ray, t_sphere sp, t_rec *rec) 
{
	t_vec3	oc;
	double	discriminant;
	double	a;
	double	half_b;
	double	root;

	vec_minus(&oc, ray.p, sp.p);
	a = vec_dot(ray.dir, ray.dir);
	half_b = vec_dot(oc, ray.dir);
	discriminant = pow(half_b, 2) - (a * (vec_dot(oc, oc) - pow(sp.r, 2)));
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < T_MIN || root > T_MAX)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < T_MIN || root > T_MAX)
			return (false);
	}
	rec->t = root;
	ray_at(&rec->p, ray, root);
	vec_minus(&rec->norm, rec->p, sp.p);
	vec_convert_unit(rec->norm, &rec->norm);
	set_face(ray, rec);
	return (true);
}