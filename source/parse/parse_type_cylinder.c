/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:11:30 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:11:35 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"
#include "utils.h"
#include "vector.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static t_cylinder	*add_cylinder(t_descr *descr);

void	parse_cy(char **input, t_descr *descr)
{
	t_cylinder	*new;

	if (check_dcharp_num(6, input) == false)
		err_exit_descr(descr, input);
	new = add_cylinder(descr);
	if (!check_syntax_vec(input[1]) || !check_syntax_vec(input[2])
		|| !check_syntax_dbl(input[3]) || !check_syntax_dbl(input[4])
		|| !check_syntax_rgb(input[5]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &new->p, NULL, false);
	if (convert_vec3(input[2], &new->o, NULL, true) == false)
		err_exit_descr(descr, input);
	vec_convert_unit(new->o, &new->o);
	new->r = convert_double(input[3]);
	new->h = convert_double(input[4]);
	if (convert_rgb(input[5], &(new->c)) == false)
		err_exit_descr(descr, input);
}

static t_cylinder	*add_cylinder(t_descr *descr)
{
	int			i;
	t_cylinder	**new_list;
	t_cylinder	*new;

	new_list = malloc(sizeof(t_cylinder *) * (descr->cnt.cy_cnt + 2));
	if (new_list == NULL)
		err_exit("add_cylinder", errno);
	i = 0;
	while (i < descr->cnt.cy_cnt)
	{
		new_list[i] = (descr->cy)[i];
		i++;
	}
	if (descr->cy != NULL)
		free(descr->cy);
	descr->cy = new_list;
	descr->cnt.cy_cnt++;
	new = malloc(sizeof(t_cylinder));
	if (new == NULL)
		err_exit("add_cylinder", errno);
	new_list[i++] = new;
	new_list[i] = NULL;
	return (new);
}
