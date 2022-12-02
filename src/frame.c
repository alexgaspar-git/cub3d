/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:11 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 15:12:43 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
			my_mlx_pixel_put(cub->data, x, y, BORDER);
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
			my_mlx_pixel_put(cub->data, x, y, BORDER);
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
			my_mlx_pixel_put(cub->data, x, y, BORDER);
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
			my_mlx_pixel_put(cub->data, x, y, BORDER);
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
