/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/18 23:07:45 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (x < W && y < H && x > -1 && y > -1)
				my_mlx_pixel_put(cub->data, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(char **map, t_cub *cub)
{
	int	x = 0;
	int y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square(x * cub->grid, y * cub->grid, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square(x * cub->grid, y * cub->grid, 0xAAAAAA, cub);
			if (map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square(x * cub->grid, y * cub->grid, 0xFF0000, cub);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub *cub)
{
	int	i = -3;
	int j = -3;
	int	p_size = 4;

	while (i < p_size)
	{
		j = -3;
		while (j < p_size)
		{
			if (i + cub->player->p_x < W && j + cub->player->p_y < H && i + cub->player->p_x > -1 && j + cub->player->p_y > -1)
				my_mlx_pixel_put(cub->data, i + cub->player->p_x, j + cub->player->p_y, 0x0000FF);
			j++;
		}
		i++;
	}
}

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->p_x / cub->grid);
	y = (int)(cub->player->p_y / cub->grid);
	if (x > xf)
		cub->player->p_x = ((xf + 1) * cub->grid) + 3;
	else if(x < xf)
		cub->player->p_x = (xf * cub->grid) - 4;
	if (y > yf)
		cub->player->p_y = ((yf + 1) * cub->grid) + 3;
	else if(y < yf)
		cub->player->p_y = (yf * cub->grid) - 4;
}

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x + cub->player->p_dx + 4) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dx - 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y + cub->player->p_dy + 4) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dy - 3) / cub->grid;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	return (0);
}

int	is_wall_behind(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x - cub->player->p_dx - 4) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dx + 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y - cub->player->p_dy - 4) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dy + 3) / cub->grid;
	if (cub->map[y][x] == '1')
	{
		find_wall(cub, y, x);
		return (1);
	}
	return (0);
}

void	move_player(t_cub *cub)
{
	if (cub->key->w == 1)
	{
		if (!is_wall_front(cub))
		{
			cub->player->p_x += cub->player->p_dx;
			cub->player->p_y += cub->player->p_dy;
		}
	}
	if (cub->key->s == 1)
	{
		if (!is_wall_behind(cub))
		{
			cub->player->p_x -= cub->player->p_dx;
			cub->player->p_y -= cub->player->p_dy;
		}
	}
	if (cub->key->a == 1)
	{
		cub->player->p_a += 0.1;
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a = 0;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	if (cub->key->d == 1)
	{
		cub->player->p_a -= 0.1;
		if (cub->player->p_a < 0)
			cub->player->p_a = 2 * M_PI;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
}

void	draw_rays(t_cub *cub)
{
	float	start_a = cub->player->p_a - HALF_FOV;
	int	i = 0;

	while (i < CASTED_RAYS)
	{
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cos(start_a) * 500, cub->player->p_y + -sin(start_a) * 500, 0xFFFFFF), cub);
		start_a += STEP_ANGLE;
		i++;
	}
}

t_line	init_line(int x1, int y1, int x2, int y2, int color)
{
	t_line line;

	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
	line.y2 = y2;
	line.color = color;

	return (line);
}

int	render(t_cub *cub)
{
	move_player(cub);
	draw_map(cub->map, cub);
	draw_player(cub);
	// draw_ray(cub, cub->player);
	draw_rays(cub);
	printf("p_x: %f | p_y: %f | p_dx: %f | p_dy: %f | p_a: %f\n", cub->player->p_x, cub->player->p_y, cub->player->p_dx, cub->player->p_dy, cub->player->p_a);
	printf("on tile: [%f,%f]\n", roundf(cub->player->p_x/64 - 0.5), roundf(cub->player->p_y/64 - 0.5));
	dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cub->player->p_dx * 20,  cub->player->p_y + cub->player->p_dy * 20, 0xFF00FF), cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	clear_window(cub->data);
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
