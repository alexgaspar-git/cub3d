/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:44:29 by lide              #+#    #+#             */
/*   Updated: 2022/11/08 16:17:45 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	find_wall_x(float rx, float ry)
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
	// printf("x = %f | y = %f\n", rx, ry);
	if (x == 0.000)
		return (y);
	else
		return (x);
}

void	dr_texture(t_line line, t_cub *cub, t_ray ray, int i)
{
	int		color;
	float	fx;
	int		x;
	float		diff;
	float	y;

	fx = find_wall_x(ray.rx, ray.ry);
	x = ((float)(cub->tex[i].w) * fx);//modifier 0 par direction
	diff = (float)(cub->tex[i].h) / (line.y2 - line.y1);
	// printf("x = %f\n", diff);
	y = 0;
	// printf("x = %f\n", fx);
	if (line.y1 < 0)
	{
		y = diff * -line.y1;
		line.y1 = 0;
	}
	if (line.y2 > H)
		line.y2 = H;
	while (line.y1 < line.y2)
	{
		color = get_texel_color(&cub->tex[i], x, (int)fabsf(y));//doit savoir se situer sur le mur pour savoir ou dans tex
		if (line.x1 >= 0 && line.x1 < W && line.y1 >= 0 && line.y1 < H)
			my_mlx_pixel_put(cub->data, line.x1, line.y1 ,color);
		line.y1++;
		y += diff;
		// printf("%d\n", (int)fabsf(y));
	}
}