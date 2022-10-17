/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/17 18:00:36 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player_minimap(char **map, t_cub *cub)
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

void	dr_square(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (i + cub->m_ox < W && j + cub->m_oy < H && i >= 0 && j >= 0)
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

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square(x * (cub->grid + cub->grid_gap), y * (cub->grid + cub->grid_gap), 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square(x * (cub->grid + cub->grid_gap), y * (cub->grid + cub->grid_gap), 0xAAAAAA, cub);
			if ( map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square(x * (cub->grid + cub->grid_gap), y * (cub->grid + cub->grid_gap), 0xFF0000, cub);
			x++;
		}
		y++;
	}
}

void	player(t_cub *cub)
{
	
}

int	render(t_cub *cub)
{
	// display_minimap(cub->map, cub);
	// dr_player(cub);
	// move_map(cub);
	display_map(cub->map, cub);
	player();
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	clear_window(cub->data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub *cub;

	if (argc < 2)
	{
		printf("cub3d need a map\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		printf("too much information\n");
		exit(EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		exit(EXIT_FAILURE);
	cub = init_cub(argv);
	init_hooks(cub);
	free_list(cub->pars->mlc);
	return (0);
}