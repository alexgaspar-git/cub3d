/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/17 17:04:31 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(char **map, t_cub *cub)
{
	int	x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
			{
				cub->p_x = MW / 2 - x * cub->grid - (cub->grid/2);
				cub->p_y = MH / 2 - y * cub->grid - (cub->grid/2);
				return ;
			}
			x++;
		}
		y++;
	}
}

void clear_window(t_data *data)
{
	int	x = 0;
	int	y = 0;
	
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			my_mlx_pixel_put(data, x, y, BG);
			x++;
		}
		y++;
	}
}

int	render(t_cub *cub)
{
	display_minimap(cub->map, cub);
	dr_player(cub);
	move_map(cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	clear_window(cub->data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub *cub;
	char *map[] = {
	"        1111111111111111111111111",
	"        1000000000110000000000001",
	"        1011000001110000000000001",
	"        1001000000000000000000001",
	"111111111011000001110000000000001",
	"100000000011000001110111111111111",
	"11110111111111011100000010001",
	"11110111111111011101010010001",
	"11000000110101011100000010001",
	"10000000000000001100000010001",
	"10000000000000001101010010001",
	"11000001110101011111011110N0111",
	"11110111 1110101 101111010001",
	"11111111 1111111 111111111111",
	NULL};

	(void)argc;
	(void)argv;
	cub = init_cub(map);
	init_hooks(cub);
	return (0);
}