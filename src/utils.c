/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:46:47 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/08 16:22:18 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	*xalloc(size_t size)
{
	void *a;

	a = malloc(size);
	if (!a)
		exit(EXIT_FAILURE);
	return (a);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
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
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(cub->data->mlx, cub->data->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int		mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x;

	(void)y;
	if (!old_x)
		old_x = 0;
	if (x < old_x)
	{
		cub->player->p_a += (float)(old_x - x)/500;
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a = 0;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	if (x > old_x)
	{
		cub->player->p_a -= (float)(x - old_x)/500;
		if (cub->player->p_a < 0)
			cub->player->p_a = 2 * M_PI;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	old_x = x;
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
	return (0);
}
