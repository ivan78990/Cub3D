/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:35:52 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		prms_fre(t_parameters *params, int *error)
{
	if (params->north)
		free(params->north);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	if (params->sprite)
		free(params->sprite);
	if (params->dists)
		free(params->dists);
	free(params);
	if (*error)
		err_prms(error);
	return (0);
}

int		err_prms(int *error)
{
	if (*error & (1 << 6))
		ft_putstr("Error: Cannot open file\n");
	else
	{
		if (*error & (1 << 0))
			ft_putstr("Error: No resolution parameters\n");
		if (*error & (1 << 1))
			ft_putstr("Error: Wrong resolution parameters\n");
		if (*error & (1 << 2))
			ft_putstr("Error: Texture parameters missing\n");
		if (*error & (1 << 3))
			ft_putstr("Error: Two much texture parameters\n");
		if (*error & (1 << 4))
			ft_putstr("Error:Wrong color parameters of ceiling or floor\n");
		if (*error & (1 << 5))
			ft_putstr("Error: Allocating error\n");
	}
	return (0);
}

int		init_prms(t_parameters *params)
{
	if (params)
	{
		params->res_h = -1;
		params->res_v = -1;
		params->north = NULL;
		params->south = NULL;
		params->west = NULL;
		params->east = NULL;
		params->sprite = NULL;
		params->dists = NULL;
		params->fl_clr = -1;
		params->ceil_clr = -1;
		params->plr.pos_y = 0;
		params->plr.pos_x = 0;
		params->plr.ang_h = 0;
		return (1);
	}
	return (0);
}

int		chk_prms(t_parameters *params, int *error)
{
	*error = (params->res_h == -1 || params->res_v == -1) ? *error | 1 : *error;
	*error = (params->ceil_clr == -1 || params->fl_clr == -1) ?
		*error | (1 << 4) : *error;
	*error = (params->north) ? *error : *error | (1 << 2);
	*error = (params->south) ? *error : *error | (1 << 2);
	*error = (params->west) ? *error : *error | (1 << 2);
	*error = (params->east) ? *error : *error | (1 << 2);
	*error = (params->sprite) ? *error : *error | (1 << 2);
	*error = (params->dists) ? *error : *error | (1 << 5);
	return (1);
}

int		ft_parse(char *f_name, t_parameters *params)
{
	char	*line;
	int		fd;
	int		error;

	if (-1 == (fd = open(f_name, O_RDONLY)))
	{
		ft_putstr("Error: Cannot open file\n");
		return (0);
	}
	if (init_prms(params))
	{
		error = 0;
		prs_prms(fd, params, &line, &error);
		chk_prms(params, &error);
		if (error)
			prms_fre(params, &error);
		else if (prs_mp(fd, params, &line))
		{
			close(fd);
			return (1);
		}
	}
	close(fd);
	return (0);
}
