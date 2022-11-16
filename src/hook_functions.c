/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:48:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/14 15:32:31 by algaspar         ###   ########.fr       */
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
#include <sys/time.h>

static void	fps_counter(void)
{
	static int		n_frame = 0;
	static int		second = 0;
	struct timeval	t;
	int				fps;

	fps = 0;
	n_frame++;
	gettimeofday(&t, NULL);
	if (t.tv_sec > second)
	{
		fps = n_frame;
		printf("%d\n", fps);
		n_frame = 0;
		second = t.tv_sec;
	}
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
	fps_counter();
	mlx_put_image_to_window(cub->data->mlx,
		cub->data->win, cub->data->img, 0, 0);
	return (0);
}
