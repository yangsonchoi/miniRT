#ifndef UTILS_H
# define UTILS_H

# include <errno.h>

/*
** error.c
*/
void	err_exit(char *str, int input);

/*
** get_next_line.c
*/
char	*get_next_line(int fd);

#endif