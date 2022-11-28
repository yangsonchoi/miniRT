/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:04:59 by yachoi            #+#    #+#             */
/*   Updated: 2022/11/21 12:06:01 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#include <stdio.h> // test

void	parse_scene(t_descr *descr, char *file_name)
{
	int		fd;
	char	*temp;
	char	*trim;

	if (ft_strchr(file_name, '.') && ft_strncmp(ft_strchr(file_name, '.'), \
		".rt", 3))
		err_exit("invalid file name", 0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		err_exit(file_name, errno);
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		trim = ft_strtrim(temp, "\n");
		free(temp);
		printf("parsing: %s\n", trim);
		parse_description(trim, descr);
		free(trim);
	}
	close (fd);
}
