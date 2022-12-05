/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_texture_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:44:29 by lide              #+#    #+#             */
/*   Updated: 2022/12/05 14:16:36 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

float	find_wall_x(float rx, float ry, int i)
{
	float	x;
	float	y;

	rx = rx / GRID;
	ry = ry / GRID;
	x = rx - (int)(rx);
	y = ry - (int)(ry);
	if (x < 0)
		x = 1 + x;
	if (y < 0)
		y = 1 + y;
	if (x == 0.000)
	{
		if (i == SOUTH || i == WEST)
			y = 1 - y;
		return (y);
	}
	if (i == SOUTH || i == WEST)
		x = 1 - x;
	return (x);
}

void	dr_texture(t_line line, t_cub *cub, t_ray ray, int i)
{
	int			color;
	int			x;
	float		diff;
	float		fx;
	float		y;

	fx = find_wall_x(ray.rx, ray.ry, i);
	x = ((float)(cub->tex[i].w) * fx);
	diff = (float)(cub->tex[i].h) / (line.y2 - line.y1);
	y = 0;
	if (line.y1 < 0)
	{
		y = diff * (-line.y1);
		line.y1 = 0;
	}
	if (line.y2 > H)
		line.y2 = H;
	while (line.y1 < line.y2)
	{
		color = get_texel_color(&cub->tex[i], x, (int)fabsf(y));
		if (line.x1 >= 0 && line.x1 < W && line.y1 >= 0 && line.y1 < H)
			my_mlx_pixel_put(cub->data, line.x1, line.y1, color);
		line.y1++;
		y += diff;
	}
}
