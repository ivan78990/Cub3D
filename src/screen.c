/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:39:19 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			crop_resolution(t_allrend *all)
{
	int res_h;
	int res_v;

	mlx_get_screen_size(all->win->mlx, &res_h, &res_v);
	all->prms->res_v = (all->prms->res_v > res_v) ? res_v : all->prms->res_v;
	all->prms->res_h = (all->prms->res_h > res_h) ? res_h : all->prms->res_h;
	return (0);
}

static void	*text_int(t_allrend *all, char *path)
{
	t_txt *txtr;

	if ((txtr = ft_calloc(1, sizeof(t_txt))))
		if ((txtr->img = mlx_xpm_file_to_image(all->win->mlx, path,
			&txtr->w_tex, &txtr->h_tex)))
		{
			txtr->adr = mlx_get_data_addr(txtr->img, &txtr->bpp, &txtr->line_l,
				&txtr->en);
			return (txtr);
		}
	return (NULL);
}

static void	begin_rndr(t_allrend *all)
{
	mlx_hook(all->win->win, 2, 1L << 0, key_pr, all);
	mlx_hook(all->win->win, 17, 1L << 17, my_exit, all);
	mlx_hook(all->win->win, 3, 1L << 1, key_rel, all);
	mlx_loop_hook(all->win->mlx, rndr_next_fr, all);
	mlx_loop(all->win->mlx);
}

static int	wind_init(t_allrend *all, int argc)
{
	if ((all->win = (t_win *)ft_calloc(1, sizeof(t_win))) &&
			(all->win->mlx = mlx_init()))
	{
		if (argc == 2)
			crop_resolution(all);
		if ((all->win->win = mlx_new_window(all->win->mlx,
											all->prms->res_h, all->prms->res_v,
											"cub3D")) &&
			(all->win->north = text_int(all, all->prms->north)) &&
			(all->win->south = text_int(all, all->prms->south)) &&
			(all->win->west = text_int(all, all->prms->west)) &&
			(all->win->east = text_int(all, all->prms->east)) &&
			(all->win->sprite = text_int(all, all->prms->sprite)))
			return (1);
	}
	return (0);
}

void		ft_rndr(t_parameters *params, int argc)
{
	t_allrend	*all;

	if ((all = (t_allrend *)ft_calloc(1, sizeof(t_allrend))))
	{
		all->prms = params;
		if (wind_init(all, argc))
		{
			mk_img(all);
			all->win->move_mask = 0;
			if (argc == 2)
				begin_rndr(all);
			else
				ft_scrnshot(all);
			freewin(all);
			free(all->win);
		}
		else
		{
			ft_putstr("Wrong texture path\n");
			freewin(all);
		}
	}
	else
		ft_putstr("Allocating memory error\n");
}
