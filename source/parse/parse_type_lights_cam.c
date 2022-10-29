#include "parse.h"
#include "minirt.h"
#include "utils.h"
#include "libft.h"

void	parse_al(char **input, t_descr *descr)
{
	if(descr->cnt.al_cnt != 0 || check_dcharp_num(3, input) == false)
		err_exit_descr(descr, input);	
	if (!check_syntax_dbl(input[1]) || !check_syntax_rgb(input[2]))
		err_exit_descr(descr, input);
	descr->al.r = convert_double(input[1]);
	if (descr->al.r < 0 || descr->al.r > 1)
		err_exit_descr(descr, input);
	if (convert_rgb(input[2], &(descr->al.c)) == false)
		err_exit_descr(descr, input);
	descr->cnt.al_cnt = 1;
}

void	parse_c(char **input, t_descr *descr)
{
	int	i;

	if(descr->cnt.c_cnt != 0 || check_dcharp_num(4, input) == false)
		err_exit_descr(descr, input);		
	if (!check_syntax_vec(input[1]) || !check_syntax_vec(input[2]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &(descr->c.p), NULL, false);
	if (convert_vec3(input[2], &(descr->c.o), NULL, true) == false)
		err_exit_descr(descr, input);
	i = 0;
	while (input[3][i] != 0)
	{
		if (ft_isdigit(input[3][i++]) == false)
			err_exit_descr(descr, input);
	}
	descr->c.fov = atoi(input[3]);
	if (descr->c.fov < 0 || descr->c.fov > 180)
		err_exit_descr(descr, input);
	descr->cnt.c_cnt = 1;
}

void	parse_l(char **input, t_descr *descr)
{
	if(descr->cnt.l_cnt != 0 || check_dcharp_num(4, input) == false)
		err_exit_descr(descr, input);		
	if (!check_syntax_vec(input[1]) || !check_syntax_dbl(input[2]) || !check_syntax_rgb(input[3]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &(descr->l.p), NULL, false);
	descr->l.b = convert_double(input[2]);
	if (descr->l.b < 0 || descr->l.b > 1)
		err_exit_descr(descr, input);
	if (convert_rgb(input[3], &(descr->l.c)) == false)
		err_exit_descr(descr, input);
	descr->cnt.l_cnt = 1;
}