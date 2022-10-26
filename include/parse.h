#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"
# include <stdbool.h>

enum    e_des_type
{
    AMBIENT_LIGHT,
    CAMERA,
    LIGHT,
    SPHERE,
    PLANE,
    CYLINDER,
    ELSE,
};

/*
** parse.c
*/
void	parse_scene(t_descr *descr, char *file);

/*
** parse_description.c
*/
void	parse_description(char *input, t_descr *descr);

/*
** parse_convert.c
*/
double	convert_double(char *input);
bool	convert_vec3(char *input, t_vec3 *vec, double *len, bool check);
bool	convert_rgb(char *input, t_color *dest);

/*
** parse_type_cylinder.c
*/
void parse_cy(char **input, t_descr *descr);


#endif