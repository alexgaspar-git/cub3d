/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:02:24 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/17 17:04:19 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_map(t_cub *cub)
{
	if (cub->key->w == 1)
		cub->oy += 2;
	if (cub->key->a == 1)
		cub->ox += 2;
	if (cub->key->s == 1)
		cub->oy -= 2;
	if (cub->key->d == 1)
		cub->ox -= 2;
}

void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (i + cub->ox < MW && j + cub->oy < MH && i + cub->ox >= 0 && j + cub->oy >= 0)
				my_mlx_pixel_put(cub->data, i + cub->ox, j + cub->oy, color);
			j++;
		}
		i++;
	}
}

void	dr_player(t_cub *cub)
{
	int	i = 0;
	int j = 0;
	int	p_size = 6;

	while (i < p_size)
	{
		j = 0;
		while (j < p_size)
		{
			my_mlx_pixel_put(cub->data, i + MW/2 - (p_size/2), j + MH/2 - (p_size/2) , 0x0000FF);
			j++;
		}
		i++;
	}
}


void	display_minimap(char **map, t_cub *cub)
{
	int	x = 0;
	int	y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square_mini(x * (cub->grid + cub->grid_gap) + cub->p_x, y * (cub->grid + cub->grid_gap) + cub->p_y, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square_mini(x * (cub->grid + cub->grid_gap) + cub->p_x, y * (cub->grid + cub->grid_gap) + cub->p_y, 0xAAAAAA, cub);
			if ( map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square_mini(x * (cub->grid + cub->grid_gap) + cub->p_x, y * (cub->grid + cub->grid_gap) + cub->p_y, 0xFF0000, cub);
			x++;
		}
		y++;
	}
	frame_map(cub);
}