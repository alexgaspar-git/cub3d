/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:08:47 by lide              #+#    #+#             */
/*   Updated: 2022/12/02 17:09:00 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	find_map_limits(t_parsing *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x++])
			if (x > map->x_max)
				map->x_max = x;
		y++;
	}
	map->y_max = y;
}

void	check_map2(t_parsing *map, int *player, int *x, int y)
{
	if (map->map[y][*x] != '0'
		&& map->map[y][*x] != ' ' && map->map[y][*x] != '1')
		if (++(*player) > 1)
			free_list_exit(map->mlc, "only one player is accepted", 0);
	if (map->map[y][*x] != ' ' && map->map[y][*x] != '1')
		if (y == 0 || check_map_wall(map->map, y, *x))
			free_list_exit(map->mlc, "map is not closed", 0);
	(*x)++;
}

void	check_map(t_parsing *map)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
			check_map2(map, &player, &x, y);
		y++;
	}
	if (player == 0)
		free_list_exit(map->mlc, "one player is required", 0);
	check_texture_xpm(map);
	find_map_limits(map);
}
