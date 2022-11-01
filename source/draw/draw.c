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
static bool		hit_object(t_ray ray, t_rec *rec, t_descr *descr);
static bool		hit_sphere(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr);
void	set_color(t_vec3 obj, t_ray ray, t_rec *rec, t_descr *descr);
t_vec3	diffuse_light(t_ray ray, t_rec *rec, t_descr *descr);

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
	ray.dir.x = draw.llc.x + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.x) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.x) - descr->c.p.x;
	ray.dir.y = draw.llc.y + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.y) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.y) - descr->c.p.y;
	ray.dir.z = draw.llc.z + (((double)(draw.w) / (double)(WIDTH - 1)) * draw.cam_h.z) + (((double)(draw.h) / (double)(HEIGHT - 1)) * draw.cam_v.z) - descr->c.p.z;
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

static void	draw_pixel(t_color color, t_draw draw, t_img *img)
{
	char	*dst;

	dst = img->addr + (draw.h * img->size_len + (draw.w * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color.color;
}

static bool	hit_object(t_ray ray, t_rec *rec, t_descr *descr)
{
	int	hit;
	int	i;

	hit = 0;;
	i = 0;
	rec->t_max = T_MAX;
	if (descr->sp != NULL)
	{
		while (descr->sp[i] != NULL)
			hit += hit_sphere(ray, descr->sp[i++], rec, descr);
	}
	return (hit);
}

static bool	hit_sphere(t_ray ray, t_sphere *sp, t_rec *rec, t_descr *descr) 
{
	t_vec3	oc;
	double	discriminant;
	double	a;
	double	half_b;
	double	root;

	vec_minus(&oc, ray.p, sp->p);
	a = vec_dot(ray.dir, ray.dir);
	half_b = vec_dot(oc, ray.dir);
	discriminant = pow(half_b, 2) - (a * (vec_dot(oc, oc) - pow(sp->r, 2)));
	if (discriminant < 0)
		return (false);
	root = ((half_b * -1) - sqrt(discriminant)) / a;
	if (root < T_MIN || root > rec->t_max)
	{
		root = ((half_b * -1) + sqrt(discriminant)) / a;
		if (root < T_MIN || root > rec->t_max)
			return (false);
	}
	rec->t = root;
	rec->t_max = root;
	ray_at(&rec->p, ray, root);
	vec_minus(&rec->norm, rec->p, sp->p);
	vec_convert_unit(rec->norm, &rec->norm);
	set_face(ray, rec);
	set_color(sp->c, ray, rec, descr);
	return (true);
}

void	set_color(t_vec3 obj, t_ray ray, t_rec *rec, t_descr *descr)
{
	t_vec3	light;

	light = vec_set(0, 0, 0);
	if (hit_object_shadow(*rec, descr) == false)
	{
		if (descr->cnt.l_cnt != 0)
			vec_plus(&light, light, diffuse_light(ray, rec, descr));
		if (descr->cnt.al_cnt != 0)
			vec_plus(&light, light, descr->al.cr);
	}
	vec_mul_vec(&rec->c, obj, light);
	max_color(&rec->c, rec->c);
}

t_vec3	diffuse_light(t_ray ray, t_rec *rec, t_descr *descr)
{
	t_vec3	light_dir;
	double	kd;
	t_vec3	diff_light;

	vec_minus(&light_dir, descr->l.p, rec->p);
	vec_convert_unit(light_dir, &light_dir);
	kd = fmax(vec_dot(rec->norm, light_dir), 0.0);
	vec_mul_db(&diff_light, descr->l.cb, kd);

	t_vec3	specular;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	temp;
	double	spec;
	double	ksn;
	double	ks;

    vec_mul_db(&view_dir, ray.dir, -1);
	vec_convert_unit(view_dir, &view_dir);
	vec_mul_db(&reflect_dir, light_dir, -1);
	temp = vec_dot(reflect_dir, rec->norm);
	vec_mul_db(&specular, rec->norm, temp * 2);
	vec_minus(&reflect_dir, reflect_dir, specular);
    ksn = 100; // shininess value
    ks = 0.7; // specular strength
    spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
    vec_mul_db(&specular, descr->l.cb, ks *spec);
	vec_plus(&diff_light, diff_light, specular);
	return (diff_light);
}
