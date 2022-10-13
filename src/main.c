/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/13 18:26:00 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dr_square(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (i + cub->ox < MW && j + cub->oy < MH && i + cub->ox >= 0 && j + cub->oy >= 0)
				my_mlx_pixel_put(cub->data, i + cub->ox, j + cub->oy, color);
			j++;
		}
		i++;
	}
}

void	dr_player(t_cub *cub)
{
	int	i = 0;
	int j = 0;
	int	p_size = 6;

	while (i < p_size)
	{
		j = 0;
		while (j < p_size)
		{
			my_mlx_pixel_put(cub->data, i + MW/2 - (p_size/2), j + MH/2 - (p_size/2) , 0x0000FF);
			j++;
		}
		i++;
	}
}

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
				cub->playerx = MW / 2 - x * cub->grid - (cub->grid/2);
				cub->playery = MH / 2 - y * cub->grid - (cub->grid/2);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	display_map(char **map, t_cub *cub)
{
	int	x = 0;
	int	y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square(x * (cub->grid + cub->grid_gap) + cub->playerx, y * (cub->grid + cub->grid_gap) + cub->playery, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square(x * (cub->grid + cub->grid_gap) + cub->playerx, y * (cub->grid + cub->grid_gap) + cub->playery, 0xAAAAAA, cub);
			if ( map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square(x * (cub->grid + cub->grid_gap) + cub->playerx, y * (cub->grid + cub->grid_gap) + cub->playery, 0xFF0000, cub);
			x++;
		}
		y++;
	}
	frame_map(cub);
}

void	move_map(t_cub *cub)
{
	if (cub->key->w == 1)
		cub->oy += 2;
	if (cub->key->a == 1)
		cub->ox += 2;
	if (cub->key->s == 1)
		cub->oy -= 2;
	if (cub->key->d == 1)
		cub->ox -= 2;
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
	display_map(cub->map, cub);
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