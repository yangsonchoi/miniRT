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

#endif