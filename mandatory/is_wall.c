/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:14:16 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 14:55:14 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->dx >= 0)
		x = (cub->player->x + cub->player->dx + 9) / GRID;
	else
		x = (cub->player->x + cub->player->dx - 8) / GRID;
	if (cub->player->dy >= 0)
		y = (cub->player->y + cub->player->dy + 9) / GRID;
	else
		y = (cub->player->y + cub->player->dy - 8) / GRID;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_behind(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->dx >= 0)
		x = (cub->player->x - cub->player->dx - 9) / GRID;
	else
		x = (cub->player->x - cub->player->dx + 8) / GRID;
	if (cub->player->dy >= 0)
		y = (cub->player->y - cub->player->dy - 9) / GRID;
	else
		y = (cub->player->y - cub->player->dy + 8) / GRID;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_left(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->dy >= 0)
		x = (cub->player->x + cub->player->dy + 9) / GRID;
	else
		x = (cub->player->x + cub->player->dy - 8) / GRID;
	if (cub->player->dx >= 0)
		y = (cub->player->y - cub->player->dx - 9) / GRID;
	else
		y = (cub->player->y - cub->player->dx + 8) / GRID;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_right(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->dy >= 0)
		x = (cub->player->x - cub->player->dy - 9) / GRID;
	else
		x = (cub->player->x - cub->player->dy + 8) / GRID;
	if (cub->player->dx >= 0)
		y = (cub->player->y + cub->player->dx + 9) / GRID;
	else
		y = (cub->player->y + cub->player->dx - 8) / GRID;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}
