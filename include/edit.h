#ifndef EDIT_H
# define EDIT_H

# include "minirt.h"
# include <stdbool.h>

# define KEY_ESC	53
# define KEY_E		14
# define KEY_C		8
# define KEY_P		35
# define KEY_Y		16
# define KEY_Q		12
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_U		32
# define KEY_I		34
# define KEY_O		31
# define KEY_J		38
# define KEY_K		40
# define KEY_L		37
# define KEY_MINUS	27
# define KEY_PLUS	24
# define KEY_ENTER	36
# define KEY_1		18
# define KEY_2		19
# define KEY_3		20
# define KEY_4		21
# define KEY_5		23
# define KEY_6		22
# define KEY_7		26
# define KEY_8		28
# define KEY_9		25
# define KEY_0		29

/*
** edit.c
*/
bool	edit_mode(int key_input, t_vars *vars);
void	edit_on(t_vars *vars);
void	edit_off(t_vars *vars);

/*
** edit_light_camera.c
*/
bool	edit_ambient_light(int key_input, t_vars *vars);
bool	edit_light(int key_input, t_vars *vars);
bool	edit_camera(int key_input, t_vars *vars);

/*
** edit_object.c
*/
bool	edit_object(int key_input, t_vars *vars);

/*
** edit_utils.c
*/
bool	edit_move(int key_input, t_vec3 cam, t_vec3 *pos);
bool	edit_rotation(int key_input, t_vec3 *orient);
int		convert_num_key(int key_input);
bool	edit_size(int sign, double *size);

#endif