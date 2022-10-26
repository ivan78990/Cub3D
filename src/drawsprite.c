/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:35:45 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		sort_spr(t_sprt **spr)
{
	t_sprt	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!spr || !spr[0])
		return ;
	while (spr[i + 1])
	{
		j = i;
		while (spr[j + 1])
		{
			if (spr[j]->dist < spr[j + 1]->dist)
			{
				tmp = spr[j];
				spr[j] = spr[j + 1];
				spr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void		ready_spr(t_allrend *all)
{
	int			i;

	i = 0;
	while (all->prms->sprites[i])
	{
		spr_prms(all->prms->sprites[i++], all->prms->plr);
	}
	sort_spr(all->prms->sprites);
}

static double	fnd_ang(double plr_ang, double spr_ang)
{
	double ang;

	ang = plr_ang - spr_ang;
	ang -= (ang > M_PI * 2) ? M_PI * 2 : 0;
	ang += (ang < 0) ? M_PI * 2 : 0;
	return (ang);
}

static int		ch_ang(double ang)
{
	if ((ang < (M_PI / 2) || ang > (3 * M_PI / 2)))
		return (1);
	return (0);
}

void			dr_sprt(t_allrend *all)
{
	int		i;
	int		j;
	int		h;
	double	ang;
	int		sz;

	i = 0;
	ready_spr(all);
	while (all->prms->sprites[i])
	{
		ang = fnd_ang(all->prms->plr.ang_h, all->prms->sprites[i]->angle);
		h = (int)((0.5 + sin(ang)) * all->prms->res_h);
		sz = (int)((double)all->prms->res_h / 2 / tan(M_PI / 6) /
			all->prms->sprites[i]->dist);
		j = h - sz / 2;
		while (j < h + sz / 2)
		{
			if (j > 0 && j < all->prms->res_h && ch_ang(ang) &&
				all->prms->dists[j] > all->prms->sprites[i]->dist)
				line_txt(all, j, sz | (((j - h + sz / 2) * 255 / sz) << 16));
			j++;
		}
		i++;
	}
}
