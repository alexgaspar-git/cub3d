/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/10 20:53:10 by algaspar         ###   ########.fr       */
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

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_A || keycode == 97)
		cub->key.a = 1;
	else if (keycode == KEY_W || keycode == 119)
		cub->key.w = 1;
	else if (keycode == KEY_S || keycode == 115)
		cub->key.s = 1;
	else if (keycode == KEY_D || keycode == 100)
		cub->key.d = 1;
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(cub->data.mlx, cub->data.win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_A || keycode == 97)
		cub->key.a = 0;
	else if (keycode == KEY_W || keycode == 119)
		cub->key.w = 0;
	else if (keycode == KEY_S || keycode == 115)
		cub->key.s = 0;
	else if (keycode == KEY_D || keycode == 100)
		cub->key.d = 0;
	return (0);
}

void draw_square(int x, int y, t_data *data, int color)
{
	int	mx;
	int my;

	mx = x;
	my = y;

	while (x <= mx + 25)
	{
		y = my;
		while (y <= my + 25)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	key_move(t_cub *cub)
{
	static int xsq = 300;
	static int ysq = 300;
	
	draw_square(xsq, ysq, &cub->data, 0x000000);
	if (cub->key.w == 1)
		ysq -= 4;
	if (cub->key.s == 1)
		ysq += 4;
	if (cub->key.a == 1)
		xsq -= 4;
	if (cub->key.d == 1)
		xsq += 4;
	draw_square(xsq, ysq, &cub->data, 0xFFFFFF);
	return (0);
}


int	main(int argc, char **argv)
{
	t_cub cub;

	(void)argc;
	(void)argv;
	cub.data.mlx = mlx_init();
	cub.data.win = mlx_new_window(cub.data.mlx, 1600, 900, "cub3d");
	cub.data.img = mlx_new_image(cub.data.mlx, 1600, 900);
	cub.data.addr = mlx_get_data_addr(cub.data.img, &cub.data.bits_per_pixel, &cub.data.line_length, &cub.data.endian);
	cub.key.w = 0;
	cub.key.a = 0;
	cub.key.s = 0;
	cub.key.d = 0;
	mlx_hook(cub.data.win, ON_KEYDOWN, 1L<<0, key_press, &cub);
	mlx_hook(cub.data.win, ON_KEYUP, 1L<<1, key_release, &cub);
	mlx_hook(cub.data.win, ON_DESTROY, 1L<<2, close_window, &cub.data);
	mlx_loop_hook(cub.data.mlx, &key_move, &cub);
	mlx_loop(cub.data.mlx);
	return (0);
}