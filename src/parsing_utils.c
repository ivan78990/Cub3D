/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:36:22 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mp_ln(char *line)
{
	int	result;

	result = 0;
	if (*line)
		result = 1;
	while (*line)
		if (!ft_strchr(" 012NSWE", *line++))
			return (0);
	return (result);
}

int		ft_clr(const char *str, int i, int *clr, int *error)
{
	i = ft_spaceskip(str, i);
	if (ft_isdigit(str[i]))
	{
		*clr = 0;
		while (ft_isdigit(str[i]) && *clr < 256 && *clr >= 0)
			*clr = *clr * 10 + (str[i++] - '0');
		return (ft_spaceskip(str, i));
	}
	*error = *error | (1 << 4);
	return (i);
}

int		is_clr(int color)
{
	return (color >= 0 && color <= 255);
}

int		ft_clrs(const char *line, int color, int *error)
{
	int i;
	int blue;
	int red;
	int green;

	i = 1;
	if (color != -1)
		*error = *error | (1 << 4);
	i = ft_clr(line, i, &red, error);
	if (line[i++] != ',')
		*error = *error | (1 << 4);
	i = ft_clr(line, i, &green, error);
	if (line[i++] != ',')
		*error = *error | (1 << 4);
	i = ft_clr(line, i, &blue, error);
	i = ft_spaceskip(line, i);
	if (line[i] || !is_clr(red) || !is_clr(green) || !is_clr(blue))
		*error = *error | (1 << 4);
	return (red << 16 | green << 8 | blue);
}
