/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:49:02 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 17:32:35 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	close_window(t_cub *cub)
{
	mlx_destroy_image(cub->data->mlx, cub->data->img);
	mlx_destroy_window(cub->data->mlx, cub->data->win);
	free_list(cub->pars->mlc);
	exit(EXIT_SUCCESS);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x = -10000000;

	if (old_x == -10000000)
		old_x = x;
	(void)y;
	if (x < old_x)
	{
		cub->player->ang += (float)(old_x - x) / 500;
		if (cub->player->ang > 2 * M_PI)
			cub->player->ang = 0;
		cub->player->dx = cos(cub->player->ang) * 5;
		cub->player->dy = -sin(cub->player->ang) * 5;
	}
	if (x > old_x)
	{
		cub->player->ang -= (float)(x - old_x) / 500;
		if (cub->player->ang < 0)
			cub->player->ang = 2 * M_PI;
		cub->player->dx = cos(cub->player->ang) * 5;
		cub->player->dy = -sin(cub->player->ang) * 5;
	}
	old_x = x;
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->key->a = 1;
	else if (keycode == KEY_W)
		cub->key->w = 1;
	else if (keycode == KEY_S)
		cub->key->s = 1;
	else if (keycode == KEY_D)
		cub->key->d = 1;
	else if (keycode == KEY_E)
		cub->key->e *= -1;
	else if (keycode == KEY_LEFT)
		cub->key->left = 1;
	else if (keycode == KEY_RIGHT)
		cub->key->right = 1;
	else if (keycode == KEY_SHIFT)
		cub->key->shift = 1;
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_image(cub->data->mlx, cub->data->img);
		mlx_destroy_window(cub->data->mlx, cub->data->win);
		free_list(cub->pars->mlc);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_A)
		cub->key->a = 0;
	else if (keycode == KEY_W)
		cub->key->w = 0;
	else if (keycode == KEY_S)
		cub->key->s = 0;
	else if (keycode == KEY_D)
		cub->key->d = 0;
	else if (keycode == KEY_LEFT)
		cub->key->left = 0;
	else if (keycode == KEY_RIGHT)
		cub->key->right = 0;
	else if (keycode == KEY_SHIFT)
		cub->key->shift = 0;
	return (0);
}

int	render(t_cub *cub)
{
	static unsigned int	check = -1;

	if (cub->key->e != check)
	{
		change_door(cub);
		check = cub->key->e;
	}
	draw_rays(cub);
	minimap(cub->map, cub);
	move_player(cub);
	mlx_put_image_to_window(cub->data->mlx,
		cub->data->win, cub->data->img, 0, 0);
	return (0);
}
