/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:48 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:15:50 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"

#include <math.h>
#include <stdbool.h>

static t_vec3	diffuse_light(t_rec *rec, t_descr *descr);

void	set_color(t_vec3 obj, t_rec *rec, t_descr *descr)
{
	t_vec3	light;

	light = vec_set(0.0, 0.0, 0.0);
	if (hit_object_shadow(*rec, descr) == false)
	{
		if (descr->cnt.l_cnt != 0)
			vec_plus(&light, light, diffuse_light(rec, descr));
	}
	if (descr->cnt.al_cnt != 0)
		vec_plus(&light, light, descr->al.cr);
	vec_mul_vec(&rec->c, obj, light);
	max_color(&rec->c, rec->c);
}

static t_vec3	diffuse_light(t_rec *rec, t_descr *descr)
{
	t_vec3	light_dir;
	double	kd;
	t_vec3	diff_light;

	vec_minus(&light_dir, descr->l.p, rec->p);
	vec_convert_unit(light_dir, &light_dir);
	kd = fmax(vec_dot(rec->norm, light_dir), 0.0);
	vec_mul_db(&diff_light, descr->l.cb, kd);
	return (diff_light);
}
