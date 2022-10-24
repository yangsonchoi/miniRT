/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ean <ean@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:52:20 by ean               #+#    #+#             */
/*   Updated: 2022/10/19 19:24:26 by ean              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "libft.h"

#define BUFFER_SIZE 4096

static bool	flush_buffer(char **p_buf, char **p_line);
static bool	get_next_chunk(int fd, char **p_buf, char **p_line);
static void	process_last_buffer(char **p_buf, char *p_delim, char **p_line);

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*ret;
	char		*p_delim;

	if (BUFFER_SIZE < 1)
		return (NULL);
	ret = NULL;
	p_delim = NULL;
	if (buf)
		p_delim = ft_strchr(buf, '\n');
	while (!p_delim)
	{
		if (!flush_buffer(&buf, &ret) || !get_next_chunk(fd, &buf, &ret))
			break ;
		p_delim = ft_strchr(buf, '\n');
	}
	if (p_delim)
		process_last_buffer(&buf, p_delim, &ret);
	return (ret);
}

static bool	flush_buffer(char **p_buf, char **p_line)
{
	char	*temp;

	if (!*p_buf)
		return (true);
	temp = NULL;
	if (*p_line)
		temp = ft_strjoin(*p_line, *p_buf);
	else
		temp = ft_strjoin("", *p_buf);
	free(*p_buf);
	*p_buf = NULL;
	free(*p_line);
	*p_line = temp;
	if (*p_line)
		return (true);
	return (false);
}

static bool	get_next_chunk(int fd, char **p_buf, char **p_line)
{
	int		n_read;

	n_read = -1;
	*p_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*p_buf)
		n_read = read(fd, *p_buf, BUFFER_SIZE);
	if (n_read < 1)
	{
		free(*p_buf);
		*p_buf = NULL;
		if (n_read == -1)
		{
			free(*p_line);
			*p_line = NULL;
		}
		return (false);
	}
	(*p_buf)[n_read] = '\0';
	return (true);
}

static void	process_last_buffer(char **p_buf, char *p_delim, char **p_line)
{
	char	*temp;

	temp = NULL;
	if (*(p_delim + 1))
	{
		temp = ft_strdup(p_delim + 1);
		if (!temp)
		{
			free(*p_buf);
			*p_buf = NULL;
			free(*p_line);
			*p_line = NULL;
			return ;
		}
		*(p_delim + 1) = '\0';
	}
	if (!flush_buffer(p_buf, p_line))
	{
		free(temp);
		return ;
	}
	*p_buf = temp;
}
