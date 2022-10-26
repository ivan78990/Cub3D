/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:46:52 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	diry_check(t_plr *plr, double angle)
{
	t_plr	p;

	p = *plr;
	if (angle > 0 && angle < M_PI)
	{
		if (p.pos_y == floor(p.pos_y))
			p.pos_y--;
		else
			p.pos_y = floor(p.pos_y);
	}
	else
	{
		if (p.pos_y == ceil(p.pos_y))
			p.pos_y++;
		else
			p.pos_y = ceil(p.pos_y);
	}
	return ((p.pos_y - plr->pos_y) / sin(angle));
}

static double	dirx_check(t_plr *plr, double ang)
{
	t_plr	pl;

	pl = *plr;
	if (ang > 3 * M_PI_2 || ang < M_PI_2)
	{
		if (pl.pos_x == ceil(pl.pos_x))
			pl.pos_x++;
		else
			pl.pos_x = ceil(pl.pos_x);
	}
	else
	{
		if (pl.pos_x == floor(pl.pos_x))
			pl.pos_x--;
		else
			pl.pos_x = floor(pl.pos_x);
	}
	return ((pl.pos_x - plr->pos_x) / cos(ang));
}

static double	angle_check(t_allrend *all, int i)
{
	double		ang;

	ang = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 * all->prms->res_h));
	(ang < 0) ? ang += 2 * M_PI : ang;
	(ang > 2 * M_PI) ? ang -= 2 * M_PI : ang;
	return (ang);
}

static int		dir(t_plr *p, double angle, double d, char dir)
{
	int g;

	if (dir == 'x')
	{
		p->pos_x += d * cos(angle);
		p->pos_y -= d * sin(angle);
		g = ((int)((p->pos_y - floor(p->pos_y)) * 255) << 16);
		g = (angle > M_PI_2 && angle < 3 * M_PI_2) ? g | WS : g | ES;
	}
	else
	{
		p->pos_y += d * sin(angle);
		p->pos_x -= d * cos(angle);
		g = ((int)((p->pos_x - floor(p->pos_x)) * 255) << 16);
		g = (angle > 0 && angle < M_PI) ? g | NT : g | ST;
	}
	return (g);
}

int				get_height(t_allrend *all, int i)
{
	t_plr	p;
	int		m;
	double	dx;
	double	dy;
	double	angle;

	p = all->prms->plr;
	angle = angle_check(all, i);
	while (all->prms->map[(int)p.pos_y][(int)p.pos_x])
	{
		dx = dirx_check(&p, angle);
		dy = diry_check(&p, angle);
		if (fabs(dy) > fabs(dx))
			if ((m = dir(&p, angle, dx, 'x')) && is_wall(all, p, angle, 'v'))
				break ;
		if (fabs(dy) <= fabs(dx))
			if ((m = dir(&p, angle, dy, 'y')) && is_wall(all, p, angle, 'h'))
				break ;
	}
	all->prms->dists[i] = sqrt(pow(p.pos_x - all->prms->plr.pos_x, 2) +
		pow(p.pos_y - all->prms->plr.pos_y, 2)) * cos(angle -
			all->prms->plr.ang_h);
	return ((int)((double)all->prms->res_h / 2 / tan(M_PI / 6) /
		all->prms->dists[i]) | m);
}
