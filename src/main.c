/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:34:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/03 16:59:47 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	draw_bg(t_cub *cub)
{
	int	x = 0;
	int	y = 0;

	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			if (y < H / 2)
				my_mlx_pixel_put(cub->data, x, y, cub->c);
			else
				my_mlx_pixel_put(cub->data, x, y, cub->f);
			x++;
		}
		y++;
	}
}

void	open_door(char ***map, int x, int y)
{
	if (*map[y][x] == 'P')
		*map[y][x] = 'O';
	else
		*map[y][x] = 'P';
}

void	change_door(t_cub *cub)
{
	int	x;
	int	y;
	int	check;

	check = 0;
	x = cub->player->p_x / GRID;
	y = cub->player->p_y / GRID;
	if (cub->player->p_dx > 0 && cub->map[y][x + 1] && (cub->map[y][x + 1] == 'P' || cub->map[y][x + 1] == 'O'))
		open_door(&cub->map, x + 1, y);
	else if (cub->player->p_dx < 0 && cub->map[y][x - 1] && (cub->map[y][x - 1] == 'P' || cub->map[y][x - 1] == 'O'))
		open_door(&cub->map, x - 1, y);
	if (cub->player->p_dy > 0 && cub->map[y + 1][x] && (cub->map[y + 1][x] == 'P' || cub->map[y + 1][x] == 'O'))
		open_door(&cub->map, x, y + 1);
	else if (cub->player->p_dy < 0 && cub->map[y - 1][x] && (cub->map[y - 1][x] == 'P' || cub->map[y - 1][x] == 'O'))
		open_door(&cub->map, x, y - 1);
}

int	render(t_cub *cub)
{
	if (cub->key->e == 1)
		change_door(cub);
	move_player(cub);
	draw_rays(cub);
	draw_map(cub->map, cub);
	draw_player(cub);
	dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cub->player->p_dx * 20,  cub->player->p_y + cub->player->p_dy * 20, 0xFF00FF), cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	draw_bg(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub *cub;

	if (argc < 2)
	{
		printf("cub3d needs a map\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		printf("too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		exit(EXIT_FAILURE);
	cub = init_cub(argv);
	init_hooks(cub);
	free_list(cub->pars->mlc);
	return (0);
}
