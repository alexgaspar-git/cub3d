/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brouillon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:37:30 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/12 15:53:47 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_A || keycode == 97)
		cub->key->a = 1;
	else if (keycode == KEY_W || keycode == 119)
		cub->key->w = 1;
	else if (keycode == KEY_S || keycode == 115)
		cub->key->s = 1;
	else if (keycode == KEY_D || keycode == 100)
		cub->key->d = 1;
	else if (keycode == KEY_Q || keycode == 100)
		cub->key->q = 1;
	else if (keycode == KEY_E || keycode == 100)
		cub->key->e = 1;
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(cub->data->mlx, cub->data->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_A || keycode == 97)
		cub->key->a = 0;
	else if (keycode == KEY_W || keycode == 119)
		cub->key->w = 0;
	else if (keycode == KEY_S || keycode == 115)
		cub->key->s = 0;
	else if (keycode == KEY_D || keycode == 100)
		cub->key->d = 0;
	else if (keycode == KEY_Q || keycode == 100)
		cub->key->q = 0;
	else if (keycode == KEY_E || keycode == 100)
		cub->key->e = 0;
	return (0);
}

void draw_triangle(int x, int y, t_data *data, int color, int alpha)
{
	t_line line;


	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

//x = xcos0 - ysin0
//y = xsin0 + ycos0

int	key_move(t_cub *cub)
{
	static int xi = 300;
	static int yi = 300;
	static double alpha = 2.00;

	draw_triangle(xi, yi, cub->data, 0x000000, alpha);
	if (cub->key->w == 1)
		yi -= 2;
	if (cub->key->s == 1)
		yi += 2;
	if (cub->key->a == 1)
		xi -= 2;
	if (cub->key->d == 1)
		xi += 2;
	if (cub->key->q == 1)
		alpha += 0.05;
	if (cub->key->e == 1)
		alpha -= 0.05;
	draw_triangle(xi, yi, cub->data, 0xFFFFFF, alpha);
	return (0);
}
// int main()
// {
	// mlx_hook(cub->data->win, ON_KEYUP, 1L<<1, key_release, cub);
	// mlx_loop_hook(cub->data->mlx, &key_move, cub);
// }