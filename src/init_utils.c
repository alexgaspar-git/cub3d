/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:00:54 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 18:21:59 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	init_line(int x1, int y1, int x2, int y2, int color)
{
	t_line	line;

	line.x1 = x1;
	line.y1 = y1;
	line.x2 = x2;
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
	ray.aTan = -1 / tan(ang);
	ray.nTan = -tan(ang);
	ray.dir = 0;
	return (ray);
}

void	get_dir(char pos, t_player *player)
{
	if (pos == 'N')
		player->p_a = HPI;
	else if (pos == 'E')
		player->p_a = 0;
	else if (pos == 'S')
		player->p_a = PI3;
	else
		player->p_a = PI;
}

void	get_player(char **map, t_player *player, t_cub *cub)
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
				player->p_x = x * cub->grid + (cub->grid / 2);
				player->p_y = y * cub->grid + (cub->grid / 2);
				cub->mini->p_mx = MW / 2 - x * cub->grid / 2 - (cub->grid / 4);
				cub->mini->p_my = MH / 2 - y * cub->grid / 2 - (cub->grid / 4);
				get_dir(map[y][x], player);
				return ;
			}
			x++;
		}
		y++;
	}
}
