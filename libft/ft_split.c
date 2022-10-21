/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:55:15 by yachoi            #+#    #+#             */
/*   Updated: 2022/02/09 00:22:17 by yachoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_mem(char **result, int wordcnt)
{
	int	i;

	i = 0;
	while (i <= wordcnt)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
	return (NULL);
}

static int	ft_wordcnt(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && (s[i] != c))
				i++;
		}
	}
	return (cnt);
}

static char	*ft_fillword(char *word, const char *s, int j, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		word[i] = s[j - len];
		i++;
		len--;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_fill(char **result, const char *s, char c, int wordcnt)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] && i < wordcnt)
	{
		len = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			len++;
		}
		result[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!result[i])
			return (free_mem(result, i - 1));
		ft_fillword(result[i], s, j, len);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		wordcnt;
	char	**result;

	if (!s)
		return (NULL);
	wordcnt = ft_wordcnt(s, c);
	result = (char **)malloc(sizeof(char *) * (wordcnt + 1));
	if (!result)
		return (NULL);
	ft_fill(result, s, c, wordcnt);
	return (result);
}
