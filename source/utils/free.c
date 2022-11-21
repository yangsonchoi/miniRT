/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:00:18 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:00:19 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minirt.h"

#include <stdlib.h>

void	free_dcharp(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		free(input[i]);
		i++;
	}
	free(input);
}

void	free_description(t_descr *descr)
{
	int	i;

	if (descr->sp != NULL)
	{
		i = 0;
		while ((descr->sp)[i] != NULL)
			free(descr->sp[i++]);
		free(descr->sp);
	}
	if (descr->pl != NULL)
	{
		i = 0;
		while ((descr->pl)[i] != NULL)
			free(descr->pl[i++]);
		free(descr->pl);
	}
	if (descr->sp != NULL)
	{
		i = 0;
		while ((descr->cy)[i] != NULL)
			free(descr->cy[i++]);
		free(descr->cy);
	}
}
