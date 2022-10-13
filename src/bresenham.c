/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:24:15 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/13 18:48:57 by algaspar         ###   ########.fr       */
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

// void	dr_line(t_line line, t_data *data)
// {
// 	int	ex = ft_abs(line.x2 - line.x1);
// 	int ey = ft_abs(line.y2 - line.y1);
// 	int dx = 2 * ex;
// 	int dy = 2 * ey;
// 	int dex = ex;
// 	int dey = ey;
// 	int xincr = 1;
// 	int yincr = 1;
// 	int	i = 0;

// 	if (line.x1 > line.x2)
// 		xincr = -1;
// 	if (line.y1 > line.y2)
// 		yincr = -1;
// 	if (dex >= dey)
// 	{
// 		while (i <= dex)
// 		{
// 			if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
// 				my_mlx_pixel_put(data, line.x1, line.y1, line.color);
// 			i++;
// 			line.x1 += xincr;
// 			ex -= dy;
// 			if (ex < 0)
// 			{
// 				line.y1 += yincr;
// 				ex += dx;
// 			}
// 		}
// 	}
// 	else if (dex < dey)
// 	{
// 		while (i <= dey)
// 		{
// 			if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
// 				my_mlx_pixel_put(data, line.x1, line.y1, line.color);
// 			i++;
// 			line.y1 += yincr;
// 			ey -= dx;
// 			if (ey < 0)
// 			{
// 				line.x1 += xincr;
// 				ey += dy;
// 			}
// 		}
// 	}
// }

void	dr_line_one(t_line line, t_bres bres, t_cub *cub)
{
	int	i;

	i = 0;
	while (i <= bres.cex)
	{
		if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
			my_mlx_pixel_put(cub->data, line.x1, line.y1, line.color);
		i++;
		line.x1 += bres.xincr;
		bres.ex -= bres.dy;
		if (bres.ex < 0)
		{
			line.y1 += bres.yincr;
			bres.ex += bres.dx;
		}
	}
}

void	dr_line_two(t_line line, t_bres bres, t_cub *cub)
{
	int	i;

	i = 0;
	while (i <= bres.cey)
	{
		if (line.x1 < W && line.y1 < H && line.x1 > -1 && line.y1 > -1)
			my_mlx_pixel_put(cub->data, line.x1, line.y1, line.color);
		i++;
		line.y1 += bres.yincr;
		bres.ey -= bres.dx;
		if (bres.ey < 0)
		{
			line.x1 += bres.xincr;
			bres.ey += bres.dy;
		}
	}
}

static t_bres	init_bres(t_line line)
{
	t_bres	bres;

	bres.ex = ft_abs(line.x2 - line.x1);
	bres.ey = ft_abs(line.y2 - line.y1);
	bres.dx = 2 * bres.ex;
	bres.dy = 2 * bres.ey;
	bres.xincr = 1;
	if (line.x1 > line.x2)
		bres.xincr = -1;
	bres.yincr = 1;
	if (line.y1 > line.y2)
		bres.yincr = -1;
	bres.cex = bres.ex;
	bres.cey = bres.ey;
	return (bres);
}

void	dr_line_og(t_line line, t_cub *cub)
{
	t_bres	bres;

	bres = init_bres(line);
	if (bres.ex >= bres.ey)
		dr_line_one(line, bres, cub);
	if (bres.ex < bres.ey)
		dr_line_two(line, bres, cub);
}
