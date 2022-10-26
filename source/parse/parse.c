#include "parse.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

void	parse_scene(t_descr *descr, char *file_name)
{
	int		fd;
	char	*temp;

	if (ft_strchr(file_name, '.') &&
		ft_strncmp(ft_strchr(file_name, '.'), ".rt", ft_strlen(ft_strchr(file_name, '.'))))
		err_exit("invalid file name", 0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		err_exit(file_name, errno);
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		parse_description(temp, descr);
		free(temp);
	}
	// if (check_discription(descr) == false)
	// {
	// 	free_description(descr);
	// 	err_exit("invalid scene description", 0);
	// }
	close (fd);
}