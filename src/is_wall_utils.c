/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:57:28 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 17:58:06 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_pixel(float *c, int key, int nb)
{
	if (!key)
		*c += nb;
	else
		*c -= nb;
}

void	move_pixel_n(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 10) / cub->grid);//5
	y4 = (int)((cub->player->p_y + 9) / cub->grid);//4
	x5 = (int)((cub->player->p_x - 10) / cub->grid);
	x4 = (int)((cub->player->p_x + 9) / cub->grid);
	if (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P')
	{
		if (cub->player->p_dy < -0.5 && (cub->map[y5][x] != '1' && cub->map[y5][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && (cub->map[y4][x] != '1' && cub->map[y4][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && (cub->map[y][x5] != '1' && cub->map[y][x5] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && (cub->map[y][x4] != '1' && cub->map[y][x4] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	move_pixel_s(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 10) / cub->grid);
	y4 = (int)((cub->player->p_y + 9) / cub->grid);
	x5 = (int)((cub->player->p_x - 10) / cub->grid);
	x4 = (int)((cub->player->p_x + 9) / cub->grid);
	if (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P')
	{
		if (cub->player->p_dy < -0.5 && (cub->map[y4][x] != '1' && cub->map[y4][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && (cub->map[y5][x] != '1' && cub->map[y5][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && (cub->map[y][x4] != '1' && cub->map[y][x4] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && (cub->map[y][x5] != '1' && cub->map[y][x5] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->p_x / cub->grid);
	y = (int)(cub->player->p_y / cub->grid);
	if (x > xf && (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P'))
		cub->player->p_x = ((xf + 1) * cub->grid) + 8;
	else if(x < xf && (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P'))
		cub->player->p_x = (xf * cub->grid) - 9;
	else if (y > yf)
		cub->player->p_y = ((yf + 1) * cub->grid) + 8;
	else if(y < yf)
		cub->player->p_y = (yf * cub->grid) - 9;
	if (!cub->key->s)
		move_pixel_n(cub, yf, x, y);
	else
		move_pixel_s(cub, yf, x, y);
}


int	check_corner(t_cub *cub, int x, int y)
{
	int	xi;
	int	yi;

	xi = cub->player->p_x / cub->grid;
	yi = cub->player->p_y / cub->grid;
	if(cub->map[yi][x] == '1' || cub->map[y][xi] == '1' || cub->map[yi][x] == 'P' || cub->map[y][xi] == 'P')
	{
		if (!cub->key->s)
			move_pixel_n(cub, y, xi, yi);
		else
			move_pixel_s(cub, y, xi, yi);
		return (1);
	}
	return (0);
}