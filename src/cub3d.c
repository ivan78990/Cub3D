/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:29:16 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:12 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	main_free(t_parameters *params)
{
	if (params->sprite)
		free(params->sprite);
	if (params->north)
		free(params->north);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	if (params->dists)
		free(params->dists);
	if (params->map)
		mp_free(params->map);
	free(params);
}

void	mp_free(char **map)
{
	int i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int		inpt_chk(int argc, char *argv[])
{
	if (argc == 1)
	{
		ft_putstr("Error: Argument is missing\n");
		return (0);
	}
	if (argc == 2 && ft_strlen(argv[1]) > 3 &&
		ft_strlen(ft_strnstr(argv[1], ".cub",
		ft_strlen(argv[1]))) == 4)
		return (1);
	if (argc == 3 && ft_strlen(argv[2]) == 6 &&
		ft_strlen(ft_strnstr(argv[2], "--save", ft_strlen(argv[1]))) == 6 &&
		ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) == 4)
		return (1);
	ft_putstr(WR_ARG_MSG);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_parameters *params;

	if ((params = (t_parameters *)ft_calloc(1, sizeof(t_parameters))))
	{
		if (inpt_chk(argc, argv) && (ft_parse(argv[1], params)))
		{
			ft_rndr(params, argc);
			main_free(params);
		}
	}
	else
		ft_putstr("Allocating error\n");
	ft_putstr("The end of cub3d\n");
}
