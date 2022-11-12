/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:10:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/12 21:18:00 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_dr_mini(int px, int py, int *sx, int *sy)
{
	*sx = px - 4;
	if (*sx < 0)
		*sx = 0;
	*sy = py - 4;
	if (*sy < 0)
		*sy = 0;
}

void	check_mini(int sx, int sy, t_cub *cub, char **map)
{
	if (map[sy][sx] == '1')
		dr_square_mini(sx * GRID / 2 + cub->player->mx,
			sy * GRID / 2 + cub->player->my, 0xFFFFFF, cub);
	if (map[sy][sx] == 'P')
		dr_square_mini(sx * GRID / 2 + cub->player->mx,
			sy * GRID / 2 + cub->player->my, 0x827FD2, cub);
	if (map[sy][sx] == '0')
		dr_square_mini(sx * GRID / 2 + cub->player->mx,
			sy * GRID / 2 + cub->player->my, 0xAAAAAA, cub);
	if (map[sy][sx] == 'N' || map[sy][sx] == 'E'
			|| map[sy][sx] == 'S' || map[sy][sx] == 'W')
		dr_square_mini(sx * GRID / 2 + cub->player->mx,
			sy * GRID / 2 + cub->player->my, 0x128EAF, cub);
}

void	dr_cone(t_cub *cub)
{
	int		i;
	float	ang;
	float	dx;
	float	dy;
	float	step;

	i = 0;
	ang = cub->player->ang - HALF_FOV;
	dx = cub->player->dx;
	dy = cub->player->dy;
	step = FOV / 50;
	while (i < 50)
	{
		dr_line(init_line(MW / 2, MH / 2,
				MW / 2 + dx * 3, MH / 2 + dy * 3, 0xAA343A40), cub);
		dx = cos(ang) * 5;
		dy = -sin(ang) * 5;
		ang += step;
		if (ang > PI2)
			ang -= PI2;
		i++;
	}
}

void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub)
{
	int	i;
	int	j;
	int	ox;
	int	oy;

	ox = (cub->player->cx - cub->player->x) / 2;
	oy = (cub->player->cy - cub->player->y) / 2;
	i = x;
	while (i < GRID / 2 + x)
	{
		j = y;
		while (j < GRID / 2 + y)
		{
			if (i + ox < MW && j + oy < MH && i + ox >= 0 && j + oy >= 0)
				my_mlx_pixel_put(cub->data, i + ox, j + oy, color);
			j++;
		}
		i++;
	}
}
