/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:57:28 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 16:44:50 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_pixel_check(char c)
{
	return (c != '1');
}

void	move_pixel_n(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->y - 10) / GRID);
	y4 = (int)((cub->player->y + 9) / GRID);
	x5 = (int)((cub->player->x - 10) / GRID);
	x4 = (int)((cub->player->x + 9) / GRID);
	if (cub->map[yf][x] != '1')
	{
		if (cub->player->dy < -0.5 && move_pixel_check(cub->map[y5][x]))
			add_pixel(&(cub->player->y), cub->key->s, -1);
		else if (cub->player->dy > 0.5 && move_pixel_check(cub->map[y4][x]))
			add_pixel(&(cub->player->y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->dx < -0.5 && move_pixel_check(cub->map[y][x5]))
			add_pixel(&(cub->player->x), cub->key->s, -1);
		else if (cub->player->dx > 0.5 && move_pixel_check(cub->map[y][x4]))
			add_pixel(&(cub->player->x), cub->key->s, 1);
	}
}

void	move_pixel_s(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->y - 10) / GRID);
	y4 = (int)((cub->player->y + 9) / GRID);
	x5 = (int)((cub->player->x - 10) / GRID);
	x4 = (int)((cub->player->x + 9) / GRID);
	if (cub->map[yf][x] != '1')
	{
		if (cub->player->dy < -0.5 && move_pixel_check(cub->map[y4][x]))
			add_pixel(&(cub->player->y), cub->key->s, -1);
		else if (cub->player->dy > 0.5 && move_pixel_check(cub->map[y5][x]))
			add_pixel(&(cub->player->y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->dx < -0.5 && move_pixel_check(cub->map[y][x4]))
			add_pixel(&(cub->player->x), cub->key->s, -1);
		else if (cub->player->dx > 0.5 && move_pixel_check(cub->map[y][x5]))
			add_pixel(&(cub->player->x), cub->key->s, 1);
	}
}

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->x / GRID);
	y = (int)(cub->player->y / GRID);
	if (x > xf && cub->map[yf][x] != '1')
		cub->player->x = ((xf + 1) * GRID) + 8;
	else if (x < xf && cub->map[yf][x] != '1')
		cub->player->x = (xf * GRID) - 9;
	else if (y > yf)
		cub->player->y = ((yf + 1) * GRID) + 8;
	else if (y < yf)
		cub->player->y = (yf * GRID) - 9;
	if (!cub->key->s)
		move_pixel_n(cub, yf, x, y);
	else
		move_pixel_s(cub, yf, x, y);
}

int	check_corner(t_cub *cub, int x, int y)
{
	int	xi;
	int	yi;

	xi = cub->player->x / GRID;
	yi = cub->player->y / GRID;
	if (cub->map[yi][x] == '1' || cub->map[y][xi] == '1')
	{
		if (!cub->key->s)
			move_pixel_n(cub, y, xi, yi);
		else
			move_pixel_s(cub, y, xi, yi);
		return (1);
	}
	return (0);
}
