/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:48:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/10 14:58:54 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x;

	(void)y;
	if (!old_x)
		old_x = 0;
	if (x < old_x)
	{
		cub->player->p_a += (float)(old_x - x) / 500;
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a = 0;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	if (x > old_x)
	{
		cub->player->p_a -= (float)(x - old_x) / 500;
		if (cub->player->p_a < 0)
			cub->player->p_a = 2 * M_PI;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
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
		mlx_destroy_window(cub->data->mlx, cub->data->win);
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
	dr_minimap(cub->map, cub);
	move_player(cub);
	mlx_put_image_to_window(cub->data->mlx,
		cub->data->win, cub->data->img, 0, 0);
	draw_bg(cub);
	return (0);
}
