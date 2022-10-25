#include "parse.h"
#include "minirt.h"
#include "libft.h"

#include <stdbool.h>

bool	parse_description(char *input, t_descr *descr)
{
	char **des;

	des = ft_split(input, ' ');
	if (des != NULL)
        get_des_type

		if (des_type(des) == AL)
			parse_al(des, descr)

	return ()
}

enum e_des_type des_type(char **parse)