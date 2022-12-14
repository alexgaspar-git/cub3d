/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:39:33 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/07 16:16:59 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_data	*init_data(t_cub *cub)
{
	t_data	*data;

	data = l_malloc(sizeof(t_data), &cub->pars->mlc);
	if (!data)
		print_exit("init_data", 1);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		free_list_exit(cub->pars->mlc, "init_data", 1);
	data->win = mlx_new_window(data->mlx, W, H, "cub3d");
	if (data->win == NULL)
		free_list_exit(cub->pars->mlc, "init_data", 1);
	data->img = mlx_new_image(data->mlx, W, H);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data);
}

t_player	*init_player(t_cub *cub)
{
	t_player	*player;

	player = l_malloc(sizeof(t_player), &cub->pars->mlc);
	if (!player)
		print_exit("init_player", 1);
	get_player(cub->map, player);
	player->dy = -sin(player->ang) * 5;
	player->dx = cos(player->ang) * 5;
	player->cx = player->x;
	player->cy = player->y;
	return (player);
}

t_key	*init_key(t_cub *cub)
{
	t_key	*key;

	key = l_malloc(sizeof(t_key), &cub->pars->mlc);
	if (!key)
		print_exit("init_key", 1);
	key->left = 0;
	key->right = 0;
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->e = -1;
	key->shift = 0;
	return (key);
}

t_cub	*init_cub(char **argv)
{
	t_parsing	*pars;
	t_cub		*cub;

	pars = parsing(argv, 1);
	check_map(pars);
	check_texture(pars);
	cub = l_malloc(sizeof(t_cub), &pars->mlc);
	if (!cub)
		print_exit("init_cub", 1);
	cub->pars = pars;
	cub->map = pars->map;
	cub->data = init_data(cub);
	cub->key = init_key(cub);
	cub->f = rgb_to_hex(cub->pars->f);
	cub->c = rgb_to_hex(cub->pars->c);
	cub->speed = 1;
	cub->player = init_player(cub);
	cub->tex = get_texture(cub->data, cub->pars);
	return (cub);
}
