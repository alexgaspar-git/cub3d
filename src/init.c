/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:39:33 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/20 18:53:29 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data != NULL)
	{
		data->mlx = mlx_init();
		if (data->mlx == NULL)
			return (NULL);
		data->win = mlx_new_window(data->mlx, W, H, "cub3d");
		if (data->win == NULL)
			return (NULL);
		data->img = mlx_new_image(data->mlx, W, H);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
				&data->line_length, &data->endian);
	}
	return (data);
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

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->data->win, ON_KEYUP, 1L<<1, key_release, cub);
	mlx_hook(cub->data->win, ON_KEYDOWN, 1L<<0, key_press, cub);
	mlx_hook(cub->data->win, ON_DESTRm_oy, 1L<<2, close_window, cub->data);
	mlx_loop_hook(cub->data->mlx, &render, cub);
	mlx_loop(cub->data->mlx);
}

void	pos_player(char **map, t_player *player, t_cub *cub)
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
				player->p_x = x * cub->grid;
				player->p_y = y * cub->grid;
				return ;
			}
			x++;
		}
		y++;
	}
}

t_player *init_player(t_cub *cub)
{
	t_player *player;

	player = xalloc(sizeof(t_player));
	player->p_a = M_PI / 2;
	player->p_dx = cos(player->p_a) * 5;
	player->p_dy = -sin(player->p_a) * 5;
	pos_player(cub->map, player, cub);
	return (player);
}

t_mini *init_minimap()
{
	t_mini *mini;

	mini = xalloc(sizeof(t_mini));
	mini->m_ox = 0;
	mini->m_oy = 0;
	mini->p_mx = 0;
	mini->p_mx = 0;
	return (mini);
}

t_cub	*init_cub(char **argv)
{
	t_cub	*cub;

	cub = xalloc(sizeof(t_cub));
	cub->key = xalloc(sizeof(t_key));
	cub->mini = init_minimap();
	cub->data = init_data();
	cub->pars = parsing(argv, 1);
	cub->map = cub->pars->map;
	cub->grid = GRID;
	cub->player = init_player(cub);
	find_player_mini(cub->map, cub);
	return (cub);
}
