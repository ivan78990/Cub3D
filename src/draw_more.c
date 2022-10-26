/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:00:55 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	take_pxl(t_txt *txt, int i, int h, int corx)
{
	char	*src;
	int		clr;
	int		y;
	int		x;

	y = txt->h_tex * i / h;
	x = txt->w_tex * corx / 255;
	src = txt->adr + (y * txt->line_l + x * (txt->bpp / 8));
	clr = *(int *)src;
	return (clr);
}

void		line_txt(t_allrend *all, int xpos, int h)
{
	t_txt	*tx;
	int		i;
	int		xcor;
	int		clr;

	tx = all->win->sprite;
	tx = (h & NT) ? all->win->north : tx;
	tx = (h & ST) ? all->win->south : tx;
	tx = (h & WS) ? all->win->west : tx;
	tx = (h & ES) ? all->win->east : tx;
	h = h & ~(0b1111 << 26);
	xcor = h >> 16;
	h = h & ~(0b11111111 << 16);
	i = (all->prms->res_v < h) ? (-all->prms->res_v + h) / 2 : 0;
	while (i < h)
	{
		if ((all->prms->res_v - h) / 2 + i >= all->prms->res_v)
			break ;
		if ((clr = take_pxl(tx, i, h, xcor)) > 0)
			mypxl_put(all->win, xpos, (all->prms->res_v - h) / 2 + i, clr);
		i++;
	}
}
