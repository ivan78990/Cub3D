/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 20:18:04 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	size_map(char *str, char c)
{
	size_t res;

	res = 1;
	if (!str)
		return (0);
	if (*str == 0)
		return (0);
	while (*str)
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}

static size_t	len_ar(const char *str, char c)
{
	size_t i;
	size_t l;
	size_t len;

	i = 0;
	while (str[i])
	{
		len = 0;
		while (str[i + len] && str[i + len] != c)
			len++;
		l = (len > l) ? len : l;
		i += len + 1;
	}
	return (++l);
}

static void		res_free(char **res, size_t c)
{
	while (c > 0)
		free(res[c--]);
	free(res);
}

static void		filler(char **res, char *str, size_t sz, size_t wd)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < sz)
		if ((res[i] = (char *)ft_calloc(wd, sizeof(char))))
		{
			j = 0;
			while (*str && *str != '\n')
				res[i][j++] = *str++;
			i++;
			str += 1;
		}
		else
		{
			res_free(res, i);
			break ;
		}
}

char			**split_mp(char const *str, char c)
{
	size_t	res_sz;
	char	**res;
	size_t	wd;

	if (str == NULL)
		return (NULL);
	res_sz = size_map((char *)str, c);
	wd = len_ar(str, c);
	res = (char **)ft_calloc((res_sz + 1), sizeof(char *));
	if (res)
		filler(res, (char *)str, res_sz, wd);
	return (res);
}
