/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:24:15 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/10 20:35:39 by algaspar         ###   ########.fr       */
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

void	dr_line(int x1, int y1, int x2, int y2, t_data *data)
{
	int	ex = ft_abs(x2 - x1);
	int ey = ft_abs(y2 - y1);
	int dx = 2 * ex;
	int dy = 2 * ey;
	int dex = ex;
	int dey = ey;
	int	i = 0;
	int xincr = 1;
	int yincr = 1;

	if (x1 > x2)
		xincr = -1;
	if (y1 > y2)
		yincr = -1;
	if (dex >= dey)
	{
		while (i <= dex)
		{
			if (x1 < W && y1 < H && x1 > -1 && y1 > -1)
				my_mlx_pixel_put(data, x1, y1, 0xFFFFFF);
			i++;
			x1 += xincr;
			ex -= dy;
			if (ex < 0)
			{
				y1 += yincr;
				ex += dx;
			}
		}
	}
	else if (dex < dey)
	{
		while (i <= dey)
		{
			if (x1 < W && y1 < H && x1 > -1 && y1 > -1)
				my_mlx_pixel_put(data, x1, y1, 0xFFFFFF);
			i++;
			y1 += yincr;
			ey -= dx;
			if (ey < 0)
			{
				x1 += xincr;
				ey += dy;
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}