/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:11 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/13 18:43:24 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	frame_one(t_cub *cub)
{
	int	x;
	int	y;

	x = MW;
	y = 0;
	while (x < MW + 5)
	{
		y = 0;
		while (y < MH + 5)
		{
			my_mlx_pixel_put(cub->data, x, y, border);
			y++;
		}
		x++;
	}
}

static void	frame_two(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = MH;
	while (x < MW)
	{
		y = MH;
		while (y < MH + 5)
		{
			my_mlx_pixel_put(cub->data, x, y, border);
			y++;
		}
		x++;
	}
}

static void	frame_three(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < MW)
	{
		y = 0;
		while (y <= 5)
		{
			my_mlx_pixel_put(cub->data, x, y, border);
			y++;
		}
		x++;
	}
}

static void	frame_four(t_cub *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x <= 5)
	{
		y = 0;
		while (y < MH)
		{
			my_mlx_pixel_put(cub->data, x, y, border);
			y++;
		}
		x++;
	}
}

void	frame_map(t_cub *cub)
{
	frame_one(cub);
	frame_two(cub);
	frame_three(cub);
	frame_four(cub);
}
