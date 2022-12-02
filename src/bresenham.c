/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:24:15 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 15:13:38 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	dr_line(t_line line, t_cub *cub)
{
	t_bres	bres;

	bres = init_bres(line);
	if (bres.ex >= bres.ey)
		dr_line_one(line, bres, cub);
	if (bres.ex < bres.ey)
		dr_line_two(line, bres, cub);
}
