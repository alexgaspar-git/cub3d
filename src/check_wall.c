/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:04:44 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/20 18:53:46 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->p_x / cub->grid);
	y = (int)(cub->player->p_y / cub->grid);
	if (x > xf)
		cub->player->p_x = ((xf + 1) * cub->grid) + 3;
	else if(x < xf)
		cub->player->p_x = (xf * cub->grid) - 4;
	if (y > yf)
		cub->player->p_y = ((yf + 1) * cub->grid) + 3;
	else if(y < yf)
		cub->player->p_y = (yf * cub->grid) - 4;
}

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x + cub->player->p_dx + 4) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dx - 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y + cub->player->p_dy + 4) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dy - 3) / cub->grid;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	return (0);
}

int	is_wall_behind(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x - cub->player->p_dx - 4) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dx + 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y - cub->player->p_dy - 4) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dy + 3) / cub->grid;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	return (0);
}

void	move_player(t_cub *cub)
{
	if (cub->key->w == 1)
	{
		if (!is_wall_front(cub))
		{
			cub->player->p_x += cub->player->p_dx;
			cub->player->p_y += cub->player->p_dy;
		}
	}
	if (cub->key->s == 1)
	{
		if (!is_wall_behind(cub))
		{
			cub->player->p_x -= cub->player->p_dx;
			cub->player->p_y -= cub->player->p_dy;
		}
	}
	if (cub->key->d == 1)
	{
		cub->player->p_x -= cub->player->p_dy;
		cub->player->p_y += cub->player->p_dx;
	}
	if (cub->key->a == 1)
	{
		cub->player->p_x += cub->player->p_dy;
		cub->player->p_y -= cub->player->p_dx;
	}
	if (cub->key->q == 1)
	{
		cub->player->p_a += 0.05;
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a = 0;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	if (cub->key->e == 1)
	{
		cub->player->p_a -= 0.05;
		if (cub->player->p_a < 0)
			cub->player->p_a = 2 * M_PI;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
}