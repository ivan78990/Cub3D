/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:48:45 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		dr_fc(t_allrend *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v / 2)
	{
		j = 0;
		while (j < all->prms->res_h)
			mypxl_put(all->win, j++, i, all->prms->ceil_clr);
		i++;
	}
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
			mypxl_put(all->win, j++, i, all->prms->fl_clr);
		i++;
	}
}

void		dr_wal(t_allrend *all)
{
	int i;

	i = 0;
	while (i < all->prms->res_h)
	{
		line_txt(all, i, get_height(all, i));
		i += 1;
	}
}

int			mk_img(t_allrend *all)
{
	all->win->img = mlx_new_image(all->win->mlx, all->prms->res_h,
		all->prms->res_v);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
									&all->win->line_l, &all->win->en);
	dr_fc(all);
	dr_wal(all);
	dr_sprt(all);
	return (0);
}
