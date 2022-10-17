/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:39:33 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/17 17:52:19 by algaspar         ###   ########.fr       */
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

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->data->win, ON_KEYUP, 1L<<1, key_release, cub);
	mlx_hook(cub->data->win, ON_KEYDOWN, 1L<<0, key_press, cub);
	mlx_hook(cub->data->win, ON_DESTRm_oy, 1L<<2, close_window, cub->data);
	mlx_loop_hook(cub->data->mlx, &render, cub);
	mlx_loop(cub->data->mlx);
}

t_cub	*init_cub(char **argv)
{
	t_cub	*cub;
	
	cub = xalloc(sizeof(t_cub));
	cub->key = xalloc(sizeof(t_key));
	cub->data = init_data();
	cub->pars = parsing(argv, 1);
	cub->map = cub->pars->map;
	cub->grid = 20;
	cub->grid_gap = 0;
	find_player(cub->map, cub);
	return (cub);
}