/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:02:18 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/20 18:36:38 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dr_square(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (x < W && y < H && x > -1 && y > -1)
				my_mlx_pixel_put(cub->data, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(char **map, t_cub *cub)
{
	int	x = 0;
	int y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square(x * (cub->grid + 1), y * (cub->grid + 1), 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square(x * (cub->grid + 1), y * (cub->grid + 1), 0xAAAAAA, cub);
			if (map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square(x * (cub->grid + 1), y * (cub->grid + 1), 0xFF0000, cub);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub *cub)
{
	int	i = -3;
	int j = -3;
	int	p_size = 4;

	while (i < p_size)
	{
		j = -3;
		while (j < p_size)
		{
			if (i + cub->player->p_x < W && j + cub->player->p_y < H && i + cub->player->p_x > -1 && j + cub->player->p_y > -1)
				my_mlx_pixel_put(cub->data, i + cub->player->p_x, j + cub->player->p_y, 0x0000FF);
			j++;
		}
		i++;
	}
}
