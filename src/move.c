/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:51:29 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		stepper(t_allrend *all, double i, double j)
{
	if (all->prms->map[(int)i][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)(i + D)][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)(i - D)][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)i][(int)(j + D)] == '1')
		return (0);
	if (all->prms->map[(int)i][(int)(j - D)] == '1')
		return (0);
	return (1);
}

int				move(t_allrend *all, double angle)
{
	double i;
	double j;
	double k;
	double g;

	i = all->prms->plr.pos_y / SCL;
	j = all->prms->plr.pos_x / SCL;
	k = (all->prms->plr.pos_y - SPD * sin(angle)) / SCL;
	g = (all->prms->plr.pos_x + SPD * cos(angle)) / SCL;
	if (stepper(all, k, j))
		all->prms->plr.pos_y -= SPD * sin(angle);
	if (stepper(all, i, g))
		all->prms->plr.pos_x += SPD * cos(angle);
	return (0);
}
