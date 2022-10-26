/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:41:14 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ln(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!mp_ln(map[i]))
		{
			ft_putstr("Error: Invalid map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	first_ln_chk(char *line)
{
	int i;

	i = 0;
	while (line[i])
		if (ft_strchr("20NSWE", line[i++]))
		{
			ft_putstr("Error: Invalid map\n");
			return (0);
		}
	return (1);
}

static int	zero_chk(char **map, int i, int j)
{
	if (ft_strchr("1 ", map[i][j]))
		return (1);
	if (!map[i - 1][j] || map[i - 1][j] == ' ')
		return (0);
	if (!map[i + 1][j] || map[i + 1][j] == ' ')
		return (0);
	if (!map[i][j - 1] || map[i][j - 1] == ' ')
		return (0);
	if (!map[i][j + 1] || map[i][j + 1] == ' ')
		return (0);
	return (1);
}

int			mp_chk(t_parameters *params)
{
	int	i;
	int	j;

	if (!check_ln(params->map))
		return (0);
	if (!first_ln_chk(params->map[0]))
		return (0);
	i = 1;
	while (params->map[i + 1])
	{
		j = 0;
		while (params->map[i][j])
		{
			if (!zero_chk(params->map, i, j))
			{
				ft_putstr("Error: Invalid map\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (!first_ln_chk(params->map[i]))
		return (0);
	return (1);
}
