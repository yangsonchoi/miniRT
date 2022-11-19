#ifndef CONTROL_H
# define CONTROL_H

# include "minirt.h"
# include <stdbool.h>

/*
** control.c
*/
bool	parse_control(t_descr *descr);

/*
** control_object.c
*/
int		control_object(void);

/*
** control_light_camera.c
*/
bool	change_al(t_descr *descr);

#endif