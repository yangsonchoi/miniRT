#include "parse.h"
#include "minirt.h"
#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static t_plane	*add_plane(t_descr *descr);

void parse_pl(char **input, t_descr *descr)
{
	t_plane *new;

	if (check_dcharp_num(4, input) == false)
		err_exit_descr(descr, input);
	new = add_plane(descr);
	if (!check_syntax_vec(input[1]) || !check_syntax_vec(input[2]) || !check_syntax_rgb(input[3]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &new->p, &new->d, false);
	if (convert_vec3(input[2], &new->o, NULL, true) == false)
		err_exit_descr(descr, input);
	if (convert_rgb(input[3], &(new->c)) == false)
		err_exit_descr(descr, input);
}

static t_plane	*add_plane(t_descr *descr)
{
	int i;
	t_plane **new_list;
	t_plane *new;

	new_list = malloc(sizeof(t_plane *) * (descr->cnt.pl_cnt + 2));
	if (new_list == NULL)
		err_exit("add_plane", errno);
	i = 0;
	while (i < descr->cnt.pl_cnt)
	{
		new_list[i] = (descr->pl)[i];
		i++;
	}
	if (descr->pl != NULL)
		free(descr->pl);
	descr->pl = new_list;
	descr->cnt.pl_cnt++;
	new = malloc(sizeof(t_plane));
	if (new == NULL)
		err_exit("add_plane", errno);
	new_list[i++] = new;
	new_list[i] = NULL;
	return (new);
}