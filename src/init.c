/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:39:33 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 17:42:04 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_data	*init_data(t_cub *cub)
{
	t_data	*data;//check si doit faire protection de img et addr

	data = l_malloc(sizeof(t_data), &cub->pars->mlc);
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
	mlx_hook(cub->data->win, ON_DESTROY, 1L<<2, close_window, cub->data);
	mlx_hook(cub->data->win, ON_MOUSEMOVE, 0, mouse_move, cub);
	mlx_loop_hook(cub->data->mlx, &render, cub);
	mlx_loop(cub->data->mlx);
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
				player->p_x = x * cub->grid + (cub->grid / 2);
				player->p_y = y * cub->grid + (cub->grid / 2);
				cub->mini->p_mx = MW / 2 - x * cub->grid/2 - (cub->grid/4);
				cub->mini->p_my = MH / 2 - y * cub->grid/2 - (cub->grid/4);
				get_dir(map[y][x], player);
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

	player = l_malloc(sizeof(t_player), &cub->pars->mlc);
	pos_player(cub->map, player, cub);
	player->p_dy = -sin(player->p_a) * 5;
	player->p_dx = cos(player->p_a) * 5;
	player->c_x = player->p_x;
	player->c_y = player->p_y;
	return (player);
}

t_mini *init_minimap(t_cub *cub)
{
	t_mini *mini;

	mini = l_malloc(sizeof(t_mini), &cub->pars->mlc);
	mini->m_ox = 0;
	mini->m_oy = 0;
	mini->p_mx = 0;
	mini->p_mx = 0;
	return (mini);
}

t_cub	*init_cub(char **argv)
{
	t_parsing *pars;
	t_cub	*cub;

	pars = parsing(argv, 1);
	cub = l_malloc(sizeof(t_cub), &pars->mlc);
	cub->pars = pars;
	cub->map = pars->map;
	cub->key = l_malloc(sizeof(t_key), &cub->pars->mlc);
	cub->key->e = -1;
	cub->mini = init_minimap(cub);
	cub->data = init_data(cub);
	cub->grid = GRID;
	cub->f = rgb_to_hex(cub->pars->f);
	cub->c = rgb_to_hex(cub->pars->c);
	cub->speed = 1;
	cub->player = init_player(cub);
	cub->tex = get_texture(cub->data, cub->pars);
	return (cub);
}
