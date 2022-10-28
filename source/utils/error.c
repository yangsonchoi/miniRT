#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	err_exit(char *str, int input)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("miniRT: ", 2);
	if (input == 0)
	{
		if (str != NULL)
			ft_putendl_fd(str, 2);
	}
	else
	{
		if (str != NULL)
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(strerror(input), 2);
	}
	exit(1);
}

void	err_exit_descr(t_descr *descr, char **input)
{
	if (input != NULL)
		free_description(descr);
	if (input != NULL)
		free_dcharp(input);
	err_exit("invalid scene description", 0);
}