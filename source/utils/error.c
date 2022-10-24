#include "libft.h"
#include <errno.h>
#include <stdlib.h>

void	err_exit(char *str, int input)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("miniRT: ", 2);
	if (input == 0)
		if (str != NULL)
			ft_putendl_fd(str, 2);
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