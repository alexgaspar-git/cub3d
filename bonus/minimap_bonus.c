/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:02:24 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/05 14:16:45 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	dr_player(t_cub *cub)
{
	int	i;
	int	j;
	int	p_size;

	p_size = 8;
	i = 0;
	while (i < p_size)
	{
		j = 0;
		while (j < p_size)
		{
			my_mlx_pixel_put(cub->data, i + MW / 2 - (p_size / 2),
				j + MH / 2 - (p_size / 2), 0x0000FF);
			j++;
		}
		i++;
	}
	dr_cone(cub);
}

void	minimap_bg(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			my_mlx_pixel_put(data, x, y, MMBG);
			x++;
		}
		y++;
	}
}

void	dr_minimap(char **map, t_cub *cub)
{
	int	sx;
	int	sy;
	int	px;
	int	py;

	px = (int)round_to_grid(cub->player->x) / 64;
	py = (int)round_to_grid(cub->player->y) / 64;
	init_dr_mini(px, py, &sx, &sy);
	while (sy < cub->pars->y_max && sy < py + 6)
	{
		sx = px - 6;
		if (sx < 0)
			sx = 0;
		while (sx < cub->pars->x_max && sx < px + 8)
		{
			check_mini(sx, sy, cub, map);
			sx++;
		}
		sy++;
	}
}

void	minimap(char **map, t_cub *cub)
{
	minimap_bg(cub->data);
	dr_minimap(map, cub);
	dr_player(cub);
	frame_map(cub);
}
