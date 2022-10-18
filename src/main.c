/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/18 17:11:20 by lide             ###   ########.fr       */
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
	int	i = 0;
	int j = 0;
	int	p_size = 6;

	while (i < p_size)
	{
		j = 0;
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
		cub->player->p_x = (xf + 1) * cub->grid;
	else if(x < xf)
		cub->player->p_x = xf * cub->grid;
	if (y > yf)
		cub->player->p_y = (yf + 1) * cub->grid;
	else if(y < yf)
		cub->player->p_y = yf * cub->grid;
}

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	x = (cub->player->p_x + cub->player->p_dx) / cub->grid;
	y = (cub->player->p_y + cub->player->p_dy) / cub->grid;
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

	x = (cub->player->p_x - cub->player->p_dx) / cub->grid;
	y = (cub->player->p_y - cub->player->p_dy) / cub->grid;
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
		if (cub->player->p_a < 0)
			cub->player->p_a += 2 * M_PI;
		cub->player->p_a -= 0.1;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = sin(cub->player->p_a) * 5;
	}
	if (cub->key->d == 1)
	{
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a -= 2 * M_PI;
		cub->player->p_a += 0.1;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = sin(cub->player->p_a) * 5;
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

int	round_to_grid(float p_y)
{
	return (((int)p_y>>5)<<5);
}

void	draw_ray(t_cub *cub, t_player *plr)
{
	int	r;
	int mx;
	int my;
	int dof;
	float rx;
	float ry;
	float ra;
	float xo;
	float yo;
	float aTan;
	float nTan;

	ra = plr->p_a;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		aTan = -1/tan(ra);
		if (ra > M_PI)
		{
			ry = round_to_grid(plr->p_y) - 0.0001;
			rx = (plr->p_y - ry) * aTan + plr->p_x;
			yo = -cub->grid;
			xo = -yo * aTan;
		}
		if (ra < M_PI)
		{
			ry = round_to_grid(plr->p_y) + 32;
			rx = (plr->p_y - ry) * aTan + plr->p_x;
			yo = cub->grid;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == M_PI)
		{
			rx = plr->p_x;
			ry = plr->p_y;
			dof = 8;
		}
		(void)mx;
		(void)my;
		while (dof < 8)
		{
			mx = ((int)rx) / cub->grid;
			my = ((int)ry) / cub->grid;
			if ((my < 10 && mx < 10) && mx >= 0 && my >= 0 && cub->map[my] && cub->map[my][mx] && cub->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof++;
			}
		}
		if (rx < W && ry < H && rx > -1 && ry > -1)
			dr_line(init_line(plr->p_x, plr->p_y, rx, ry, 0xFF0000), cub);

		//vertical line
		dof = 0;
		nTan = -tan(ra);
		if (ra > M_PI_2 && ra < 3 * M_PI_2)
		{
			rx = round_to_grid(plr->p_x) - 0.0001;
			ry = (plr->p_x - rx) * nTan + plr->p_y;
			xo = -cub->grid;
			yo = -xo * nTan;
		}
		if (ra < M_PI_2 || ra > 3 * M_PI_2)
		{
			rx = round_to_grid(plr->p_x) + 32;
			ry = (plr->p_x - rx) * nTan + plr->p_y;
			xo = cub->grid;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == M_PI)
		{
			rx = plr->p_x;
			ry = plr->p_y;
			dof = 8;
		}
		(void)mx;
		(void)my;
		if (rx < W && ry < H && rx > -1 && ry > -1)
			dr_line(init_line(plr->p_x, plr->p_y, rx, ry, 0xFF00FF), cub);
	}
}

int	render(t_cub *cub)
{
	// display_minimap(cub->map, cub);
	// dr_player(cub);
	// move_map(cub);
	move_player(cub);
	draw_map(cub->map, cub);
	draw_player(cub);
	draw_ray(cub, cub->player);
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
