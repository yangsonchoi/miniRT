/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_sphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:14:36 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:14:38 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static t_sphere	*add_sphere(t_descr *descr);

void	parse_sp(char **input, t_descr *descr)
{
	t_sphere	*new;

	if (check_dcharp_num(4, input) == false)
		err_exit_descr(descr, input);
	new = add_sphere(descr);
	if (!check_syntax_vec(input[1]) || !check_syntax_dbl(input[2])
		|| !check_syntax_rgb(input[3]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &new->p, NULL, false);
	new->r = convert_double(input[2]);
	if (convert_rgb(input[3], &(new->c)) == false)
		err_exit_descr(descr, input);
}

static t_sphere	*add_sphere(t_descr *descr)
{
	int			i;
	t_sphere	**new_list;
	t_sphere	*new;

	new_list = malloc(sizeof(t_sphere *) * (descr->cnt.sp_cnt + 2));
	if (new_list == NULL)
		err_exit("add_sphere", errno);
	i = 0;
	while (i < descr->cnt.sp_cnt)
	{
		new_list[i] = (descr->sp)[i];
		i++;
	}
	if (descr->sp != NULL)
		free(descr->sp);
	descr->sp = new_list;
	descr->cnt.sp_cnt++;
	new = malloc(sizeof(t_sphere));
	if (new == NULL)
		err_exit("add_sphere", errno);
	new_list[i++] = new;
	new_list[i] = NULL;
	return (new);
}
