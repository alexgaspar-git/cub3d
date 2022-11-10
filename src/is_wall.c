/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:14:16 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 18:14:23 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x + cub->player->p_dx + 9) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dx - 8) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y + cub->player->p_dy + 9) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dy - 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
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

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x - cub->player->p_dx - 9) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dx + 8) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y - cub->player->p_dy - 9) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dy + 8) / cub->grid;
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

	if (cub->player->p_dy >= 0)
		x = (cub->player->p_x + cub->player->p_dy + 9) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dy - 8) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y - cub->player->p_dx - 9) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dx + 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
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

	if (cub->player->p_dy >= 0)
		x = (cub->player->p_x - cub->player->p_dy - 9) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dy + 8) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y + cub->player->p_dx + 9) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dx - 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}