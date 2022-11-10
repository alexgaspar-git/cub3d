/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:07:43 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/10 15:00:06 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	x = cub->player->p_x / GRID;
	y = cub->player->p_y / GRID;
	if (cub->player->p_dx > 0 && cub->map[y][x + 1]
		&& (cub->map[y][x + 1] == 'P' || cub->map[y][x + 1] == 'O'))
		open_door(cub->map, x + 1, y);
	else if (cub->player->p_dx < 0 && cub->map[y][x - 1]
		&& (cub->map[y][x - 1] == 'P' || cub->map[y][x - 1] == 'O'))
		open_door(cub->map, x - 1, y);
	if (cub->player->p_dy > 0 && cub->map[y + 1][x]
		&& (cub->map[y + 1][x] == 'P' || cub->map[y + 1][x] == 'O'))
		open_door(cub->map, x, y + 1);
	else if (cub->player->p_dy < 0 && cub->map[y - 1][x]
		&& (cub->map[y - 1][x] == 'P' || cub->map[y - 1][x] == 'O'))
		open_door(cub->map, x, y - 1);
}
