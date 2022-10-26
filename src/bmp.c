/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:28:50 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clr_src(t_allrend *all, int x, int y)
{
	char	*s;
	int		clr;

	s = all->win->addr + (y * all->win->line_l + x * (all->win->bpp / 8));
	clr = *(int *)s;
	return (clr);
}

static int	bidata4(int sz, int fd)
{
	unsigned char	bf[4];

	bf[3] = (unsigned char)(sz >> 24);
	bf[2] = (unsigned char)(sz >> 16);
	bf[1] = (unsigned char)(sz >> 8);
	bf[0] = (unsigned char)(sz);
	return (write(fd, bf, 4));
}

static int	bidata2(int sz, int fd)
{
	unsigned char bf[2];

	bf[1] = (unsigned char)(sz >> 8);
	bf[0] = (unsigned char)(sz);
	return (write(fd, bf, 2));
}

static void	ft_header(t_allrend *all, int fd)
{
	int	sz;

	sz = 54 + (all->prms->res_h * all->prms->res_v * 4);
	if (write(fd, "BM", 2) && bidata4(sz, fd) &&
		bidata4(0, fd) && bidata4(54, fd) &&
		bidata4(40, fd) && bidata4(all->prms->res_h, fd) &&
		bidata4(all->prms->res_v, fd) && bidata2(1, fd) &&
		bidata2(32, fd) && bidata4(0, fd) &&
		bidata4(0, fd) && bidata4(0, fd) &&
		bidata4(0, fd) && bidata4(0, fd) &&
		bidata4(0, fd))
		ft_putstr("Write BMP-header done\n");
}

void		ft_scrnshot(t_allrend *all)
{
	int	fd;
	int	i;
	int	j;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
				0644)) > 0)
	{
		ft_header(all, fd);
		i = 0;
		while (i < all->prms->res_v)
		{
			j = 0;
			while (j < all->prms->res_h)
				bidata4(clr_src(all, j++, all->prms->res_v - i - 1), fd);
			i++;
		}
		ft_putstr("Write BMP-data done\n");
		close(fd);
	}
	else
		ft_putstr("Create/open file error\n");
}
