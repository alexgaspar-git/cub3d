/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/11 18:42:35 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dr_square(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < 50 + x)
	{
		j = y;
		while (j < 50 + y)
		{
			my_mlx_pixel_put(cub->data, i, j, color);
			j++;
		}
		i++;
	}
}

void	display_map(char **map, t_cub *cub)
{
	int	x = 0;
	int	y = 0;
	int	px = 50;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square(x * px, y * px, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square(x * px, y * px, 0xAAAAAA, cub);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_cub *cub;
	char *map[] = {"1111111111", "1000000001", "1000000001", "1000000001", "1000000001", "1000000001", "1000000001", "1000000001", "1111111111", NULL};

	(void)argc;
	(void)argv;
	cub = init_cub();
	display_map(map, cub);
	
	mlx_hook(cub->data->win, ON_KEYDOWN, 1L<<0, key_press, cub);
	mlx_hook(cub->data->win, ON_DESTROY, 1L<<2, close_window, cub->data);
	mlx_loop(cub->data->mlx);
	return (0);
}