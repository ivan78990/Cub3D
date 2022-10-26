/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freewin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:30:35 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		freetex(t_txt *txt, void *mlx)
{
	if (txt)
	{
		if (txt->img)
			mlx_destroy_image(mlx, txt->img);
		free(txt);
	}
	return (0);
}

int				freewin(t_allrend *all)
{
	if (all->win->north)
		freetex(all->win->north, all->win->mlx);
	if (all->win->south)
		freetex(all->win->south, all->win->mlx);
	if (all->win->west)
		freetex(all->win->west, all->win->mlx);
	if (all->win->east)
		freetex(all->win->east, all->win->mlx);
	if (all->win->sprite)
		freetex(all->win->sprite, all->win->mlx);
	return (0);
}
