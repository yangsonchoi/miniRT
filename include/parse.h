#ifndef PARSE_H
# define PARSE_H

# include "minirt.h"
# include <stdbool.h>

enum    e_des_type
{
    AMBIET_LIGHT,
    CAMERA,
    LGIHT,
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
bool    parse_description(char *temp, t_descr *descr);

#endif