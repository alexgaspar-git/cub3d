/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:24:15 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/11 17:44:25 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

void	dr_line(t_line line, t_data *data)
{
	int	ex = ft_abs(line.x2 - line.x1);
	int ey = ft_abs(line.y2 - line.y1);
	int dx = 2 * ex;
	int dy = 2 * ey;
	int dex = ex;
	int dey = ey;
	int xincr = 1;
	int yincr = 1;
	int	i = 0;

	if (line.x1 > line.x2)
		xincr = -1;
	if (line.y1 > line.y2)
		yincr = -1;
	if (dex >= dey)
	{
		while (i <= dex)
		{
			if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
				my_mlx_pixel_put(data, line.x1, line.y1, line.color);
			i++;
			line.x1 += xincr;
			ex -= dy;
			if (ex < 0)
			{
				line.y1 += yincr;
				ex += dx;
			}
		}
	}
	else if (dex < dey)
	{
		while (i <= dey)
		{
			if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
				my_mlx_pixel_put(data, line.x1, line.y1, line.color);
			i++;
			line.y1 += yincr;
			ey -= dx;
			if (ey < 0)
			{
				line.x1 += xincr;
				ey += dy;
			}
		}
	}
}