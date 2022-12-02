/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:49:46 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 15:13:18 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_point	init_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_line	init_line_x(t_point a, t_point b, unsigned int color)
{
	t_line	line;

	line.x1 = a.x;
	line.y1 = a.y;
	line.x2 = b.x;
	line.y2 = b.y;
	line.color = color;
	return (line);
}

t_line	init_line(int x1, int y1, int y2, int color)
{
	t_line	line;

	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x1;
	line.y2 = y2;
	line.color = color;
	return (line);
}

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->data->win, ON_KEYUP, 1L << 1, key_release, cub);
	mlx_hook(cub->data->win, ON_KEYDOWN, 1L << 0, key_press, cub);
	mlx_hook(cub->data->win, ON_DESTROY, 1L << 2, close_window, cub->data);
	mlx_hook(cub->data->win, ON_MOUSEMOVE, 0, mouse_move, cub);
	mlx_loop_hook(cub->data->mlx, &render, cub);
	mlx_loop(cub->data->mlx);
}

t_ray	init_ray(float ang)
{
	t_ray	ray;

	ray.rx = 100000;
	ray.ry = 100000;
	ray.xo = 0;
	ray.yo = 0;
	ray.a_tan = -1 / tan(ang);
	ray.n_tan = -tan(ang);
	ray.dir = 0;
	ray.dist = 0;
	ray.line = 0;
	ray.line_o = 0;
	ray.cam_a = 0;
	return (ray);
}

void	get_dir(char pos, t_player *player)
{
	if (pos == 'N')
		player->ang = (PI / 2);
	else if (pos == 'E')
		player->ang = 0;
	else if (pos == 'S')
		player->ang = (3 * (PI / 2));
	else
		player->ang = PI;
}

void	get_player(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'S' || map[y][x] == 'W')
			{
				player->x = x * GRID + (GRID / 2);
				player->y = y * GRID + (GRID / 2);
				player->mx = MW / 2 - x * GRID / 2 - (GRID / 4);
				player->my = MH / 2 - y * GRID / 2 - (GRID / 4);
				get_dir(map[y][x], player);
				return ;
			}
			x++;
		}
		y++;
	}
}
