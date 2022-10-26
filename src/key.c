/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:35:27 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pr(int key, t_allrend *all)
{
	if (key == 13)
		all->win->move_mask = all->win->move_mask | FORW;
	if (key == 0)
		all->win->move_mask = all->win->move_mask | MV_L;
	if (key == 1)
		all->win->move_mask = all->win->move_mask | BACKW;
	if (key == 2)
		all->win->move_mask = all->win->move_mask | MV_R;
	if (key == 124)
		all->win->move_mask = all->win->move_mask | RT_L;
	if (key == 123)
		all->win->move_mask = all->win->move_mask | RT_R;
	if (key == 53)
		all->win->move_mask = all->win->move_mask | ESC;
	return (0);
}

int		key_rel(int key, t_allrend *all)
{
	if (key == 13)
		all->win->move_mask = all->win->move_mask & ~FORW;
	if (key == 0)
		all->win->move_mask = all->win->move_mask & ~MV_L;
	if (key == 1)
		all->win->move_mask = all->win->move_mask & ~BACKW;
	if (key == 2)
		all->win->move_mask = all->win->move_mask & ~MV_R;
	if (key == 124)
		all->win->move_mask = all->win->move_mask & ~RT_L;
	if (key == 123)
		all->win->move_mask = all->win->move_mask & ~RT_R;
	return (0);
}

int		rndr_next_fr(t_allrend *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->win->move_mask & FORW)
		move(all, all->prms->plr.ang_h);
	if (all->win->move_mask & MV_L)
		move(all, all->prms->plr.ang_h + M_PI_2);
	if (all->win->move_mask & MV_R)
		move(all, all->prms->plr.ang_h - M_PI_2);
	if (all->win->move_mask & BACKW)
		move(all, all->prms->plr.ang_h + M_PI);
	if (all->win->move_mask & RT_L)
		all->prms->plr.ang_h -= 0.06f;
	if (all->win->move_mask & RT_R)
		all->prms->plr.ang_h += 0.06f;
	if (all->win->move_mask & ESC)
		exit(0);
	all->prms->plr.ang_h -= (all->prms->plr.ang_h > M_PI * 2) ? M_PI * 2
		: 0;
	all->prms->plr.ang_h += (all->prms->plr.ang_h < 0) ? M_PI * 2 : 0;
	mk_img(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	return (1);
}

int		my_exit(t_allrend *all)
{
	(void)all;
	exit(0);
}
