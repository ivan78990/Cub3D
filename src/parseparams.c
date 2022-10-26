/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:39:00 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				skip_n(const char *s, int i)
{
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (i);
}

int				ft_rezol(t_parameters *params, const char *ln, int *error)
{
	int i;

	i = ft_spaceskip(ln, 1);
	if (params->res_v != -1 || params->res_h != -1)
		*error = *error | (1 << 1);
	if (ft_isdigit(ln[i]) && params->res_h == -1)
		params->res_h = 0;
	while (ft_isdigit(ln[i]) && params->res_h < MAX_RE)
		params->res_h = params->res_h * 10 + (ln[i++] - '0');
	params->res_h = (params->res_h > MAX_RE) ? MAX_RE : params->res_h;
	params->res_h = (params->res_h < MIN_RE && params->res_h != -1) ?
					MIN_RE : params->res_h;
	i = skip_n(ln, i);
	i = ft_spaceskip(ln, i);
	if (ft_isdigit(ln[i]) && params->res_v == -1)
		params->res_v = 0;
	while (ft_isdigit(ln[i]) && params->res_v < MAX_RE)
		params->res_v = params->res_v * 10 + (ln[i++] - '0');
	params->res_v = (params->res_v > MAX_RE) ? MAX_RE : params->res_v;
	params->res_v = (params->res_v < MIN_RE && params->res_v != -1) ?
					MIN_RE : params->res_v;
	i = skip_n(ln, i);
	i = ft_spaceskip(ln, i);
	*error = (ln[i] != 0) ? *error | (1 << 1) : *error;
	return (i);
}

char			*ft_path(char *ln, char *pth, int i, int *er)
{
	int		j;

	i = ft_spaceskip(ln, i);
	if (pth && (*er = *er | (1 << 3)))
		free(pth);
	if ((pth = ft_calloc(ft_strlen(&ln[i]) + 1, sizeof(char))))
	{
		j = 0;
		while (ln[i])
			pth[j++] = ln[i++];
		pth[j] = 0;
		if (ft_strlen(ft_strnstr(pth, ".xpm", ft_strlen(pth))) == 4)
			return (pth);
	}
	return (0);
}

void			ln_parse(t_parameters *params, char *ln, int *er)
{
	if (ln[0] == 'R' && ln[1] == ' ')
		ft_rezol(params, ln, er);
	if (!ft_strncmp("NO ", ln, 3))
		params->north = ft_path(ln, params->north, 2, er);
	if (!ft_strncmp("SO ", ln, 3))
		params->south = ft_path(ln, params->south, 2, er);
	if (!ft_strncmp("WE ", ln, 3))
		params->west = ft_path(ln, params->west, 2, er);
	if (!ft_strncmp("EA ", ln, 3))
		params->east = ft_path(ln, params->east, 2, er);
	if (!ft_strncmp("S ", ln, 2))
		params->sprite = ft_path(ln, params->sprite, 1, er);
	if (ln[0] == 'F' && ln[1] == ' ')
		params->fl_clr = ft_clrs(ln, params->fl_clr, er);
	if (ln[0] == 'C' && ln[1] == ' ')
		params->ceil_clr = ft_clrs(ln, params->ceil_clr, er);
}

t_parameters	*prs_prms(int fd, t_parameters *params, char **line, int *error)
{
	int ret;

	while (((ret = get_next_line(fd, line)) > 0) && !mp_ln(*line))
	{
		ln_parse(params, *line, error);
		free(*line);
	}
	*error = (ret == -1) ? *error | (1 << 6) : *error;
	params->dists = (double *)ft_calloc(params->res_h, sizeof(double));
	return (params);
}
