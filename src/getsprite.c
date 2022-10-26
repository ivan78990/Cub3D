/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:30:43 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		spr_prms(t_sprt *spr, t_plr plr)
{
	double	sx;
	double	sy;

	sx = ceil(spr->pos_x) - plr.pos_x + 0.5;
	sy = ceil(spr->pos_y) - plr.pos_y + 0.5;
	spr->angle = atan2(-sy, sx);
	while (spr->angle < 0)
		spr->angle += 2 * M_PI;
	while (spr->angle > 2 * M_PI)
		spr->angle -= 2 * M_PI;
	spr->dist = sqrt(pow(sx, 2) + pow(sy, 2));
	return (0);
}

int		sprt_cnt(char **mp)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (mp[i] != 0)
	{
		j = 0;
		while (mp[i][j])
		{
			if (ft_strchr("2", mp[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

t_sprt	*sprite_pos(double j, double i)
{
	t_sprt	*sprt;

	if ((sprt = (t_sprt *)ft_calloc(1, sizeof(t_sprt))))
	{
		sprt->pos_x = (double)j;
		sprt->pos_y = (double)i;
		sprt->dist = 0;
	}
	return (sprt);
}

int		ft_sprites(t_parameters *params)
{
	int	i;
	int	j;
	int	k;

	if ((params->sprites = (t_sprt **)ft_calloc(sprt_cnt(params->map) + 1,
												sizeof(t_sprt *))))
	{
		i = 0;
		k = 0;
		while (params->map[i] != 0)
		{
			j = 0;
			while (params->map[i][j])
			{
				if (ft_strchr("2", params->map[i][j]) &&
					!(params->sprites[k++] = sprite_pos(j, i)))
					return (0);
				j++;
			}
			i++;
		}
		return (1);
	}
	return (0);
}
