/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:38:48 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		ft_ang(char c)
{
	double	ang;

	ang = 0;
	(c == 'N') ? ang = M_PI_2 : ang;
	(c == 'S') ? ang = 3 * M_PI_2 : ang;
	(c == 'W') ? ang = M_PI : ang;
	(c == 'E') ? ang = 0 : ang;
	return (ang);
}

int			prs_mp(int fd, t_parameters *params, char **line)
{
	char	*mapline;
	int		i;

	i = 1;
	mapline = NULL;
	while (i)
	{
		mapline = my_strjoin(mapline, *line);
		mapline = my_strjoin(mapline, "\n");
		free(*line);
		i = get_next_line(fd, line);
	}
	mapline = my_strjoin(mapline, *line);
	free(*line);
	((params->map = split_mp(mapline, '\n')) && mp_chk(params) &&
		ft_plr(params) && ft_sprites(params)) ? i = 1 : 0;
	free(mapline);
	return (i);
}

int			ft_plr(t_parameters *params)
{
	int			i;
	int			j;

	i = 0;
	while (params->map[i] != 0)
	{
		j = 0;
		while (params->map[i][j])
		{
			if (ft_strchr("NSWE", params->map[i][j]))
			{
				if (params->plr.pos_y > 0 && write(1, "two players\n", 13))
					return (0);
				params->plr.pos_x = (double)j + 0.5;
				params->plr.pos_y = (double)i + 0.5;
				params->plr.angle_v = 0;
				params->plr.ang_h = ft_ang(params->map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (params->plr.pos_x == 0 && write(1, "There is no player\n", 19))
		return (0);
	return (1);
}
