/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:46:47 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/28 00:16:06 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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