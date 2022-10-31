#include "parse.h"
#include "minirt.h"
#include "utils.h"
#include "libft.h"
#include "vector.h"

void	parse_al(char **input, t_descr *descr)
{
	t_vec3	c;
	double	r;
	
	if(descr->cnt.al_cnt != 0 || check_dcharp_num(3, input) == false)
		err_exit_descr(descr, input);	
	if (!check_syntax_dbl(input[1]) || !check_syntax_rgb(input[2]))
		err_exit_descr(descr, input);
	r = convert_double(input[1]);
	if (r < 0 || r > 1)
		err_exit_descr(descr, input);
	if (convert_rgb(input[2], &c) == false)
		err_exit_descr(descr, input);
	vec_mul_db(&descr->al.cr, c, r / 255);
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
	t_vec3	raw_color;
	double	b;

	if(descr->cnt.l_cnt != 0 || check_dcharp_num(4, input) == false)
		err_exit_descr(descr, input);		
	if (!check_syntax_vec(input[1]) || !check_syntax_dbl(input[2]) || !check_syntax_rgb(input[3]))
		err_exit_descr(descr, input);
	convert_vec3(input[1], &(descr->l.p), NULL, false);
	b = convert_double(input[2]);
	if (b < 0 || b > 1)
		err_exit_descr(descr, input);
	if (convert_rgb(input[3], &raw_color) == false)
		err_exit_descr(descr, input);
	vec_mul_db(&descr->l.cb, raw_color, b / 255);
	descr->cnt.l_cnt = 1;
}