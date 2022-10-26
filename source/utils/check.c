#include "utils.h"
#include "libft.h"

#include <stdbool.h>
#include <unistd.h>

bool	check_dcharp_num(int num, char **input)
{
	int	i;

	if (input == NULL)
		return (false);
	i = 0;
	while (i < num)
	{
		if (input[i] == NULL)
			return (false);
		i++;
	}
	if (input[i] != NULL)
		return (false);
	return (true);
}

bool	check_syntax_dbl(char *input)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	if (ft_isdigit(input[i]) != 1)
	{
		if (input[i] != '+' || input[i] != '-')
			z = 1;
		else
			return (false);
	}
	while (ft_isdigit(input[i + z]) == 1)
		i++;
	if (i == 0 || input[i + z] != '.')
		return (false);
	j = 1;
	while (ft_isdigit(input[i + j + z]) == 1)
		j++;
	if (j == 1 || input[i + j + z] != 0)
		return (false);
	return (true);
}

bool	check_syntax_vec(char *input)
{
	int		i;
	char	**temp;

	temp = ft_split(input, ',');
	if (check_dcharp_num(3, temp) == false)
	{
		free_dcharp(temp);
		return (false);
	}
	i = 0;
	while (temp[i] != NULL)
	{
		if (check_syntax_dbl(temp[i]) == false)
		{
			free_dcharp(temp);
			return (false);
		}
		i++;
	}
	free_dcharp(temp);
	return (true);
}

bool	check_syntax_rgb(char *input)
{
	char	**temp;
	int		i;
	int		j;
	
	temp = ft_split(input, ',');
	i = 0;
	while (temp[i] != NULL)
	{
		j = 0;
		while (ft_isdigit(temp[i][j]) == true)
			j++;
		if (j == 0 || temp[i][j] != 0)
		{
			free_dcharp(temp);
			return (false);
		}
		i++;
	}
	free_dcharp(temp);
	if (i != 3)
		return (false);
	return (true);
}
