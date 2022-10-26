/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:53:52 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_spaceskip(const char *line, int i)
{
	while ((line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
	|| (line[i] == '\r' || line[i] == '\v' || line[i] == '\f'))
		i++;
	return (i);
}

void		mypxl_put(t_win *win, int x, int y, unsigned int color)
{
	char	*dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

static int	hor_inter(int *x, int *y, double angle,
						t_plr p)
{
	if (angle > 0 && angle < M_PI)
	{
		*x = (int)p.pos_x;
		*y = (int)(p.pos_y - 1);
	}
	else
	{
		*x = (int)p.pos_x;
		*y = (int)p.pos_y;
	}
	return (0);
}

static int	ver_inter(int *x, int *y, double angle, t_plr p)
{
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
	{
		*x = (int)(p.pos_x - 1);
		*y = (int)p.pos_y;
	}
	else
	{
		*x = (int)p.pos_x;
		*y = (int)p.pos_y;
	}
	return (0);
}

int			is_wall(t_allrend *all, t_plr p, double angle, char h)
{
	int x;
	int y;

	if (h == 'h')
		hor_inter(&x, &y, angle, p);
	else
		ver_inter(&x, &y, angle, p);
	if (ft_strchr("02NSWE", all->prms->map[y][x]))
		return (0);
	return (1);
}
