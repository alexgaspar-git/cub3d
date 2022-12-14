/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:07:43 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/05 14:16:36 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	open_door(char **map, int x, int y)
{
	if ((map[y][x]) == 'P')
		(map[y][x]) = 'O';
	else
		(map[y][x]) = 'P';
}

void	change_door(t_cub *cub)
{
	int	x;
	int	y;
	int	check;

	check = 0;
	x = cub->player->x / GRID;
	y = cub->player->y / GRID;
	if (cub->player->dx > 0 && cub->map[y][x + 1]
		&& (cub->map[y][x + 1] == 'P' || cub->map[y][x + 1] == 'O'))
		open_door(cub->map, x + 1, y);
	else if (cub->player->dx < 0 && cub->map[y][x - 1]
		&& (cub->map[y][x - 1] == 'P' || cub->map[y][x - 1] == 'O'))
		open_door(cub->map, x - 1, y);
	if (cub->player->dy > 0 && cub->map[y + 1][x]
		&& (cub->map[y + 1][x] == 'P' || cub->map[y + 1][x] == 'O'))
		open_door(cub->map, x, y + 1);
	else if (cub->player->dy < 0 && cub->map[y - 1][x]
		&& (cub->map[y - 1][x] == 'P' || cub->map[y - 1][x] == 'O'))
		open_door(cub->map, x, y - 1);
}
