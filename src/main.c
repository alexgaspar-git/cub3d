/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/11 16:50:58 by algaspar         ###   ########.fr       */
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

int	mouse_func(int button, int x, int y, t_data *data)
{
	printf("button: %d | x: %d | y: %d\n", button, x, y);
	(void)data;
	// if (button == 1)
	// {
	// 	dr_line(0, 0, x, y, data);
	// }
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

t_cub	*init_cub(void)
{
	t_cub	*cub;
	
	cub = xalloc(sizeof(t_cub));
	cub->key = xalloc(sizeof(t_key));
	cub->data = init_data();
	return (cub);
}


int	main(int argc, char **argv)
{
	t_cub *cub;

	(void)argc;
	(void)argv;
	cub = init_cub();
	mlx_hook(cub->data->win, ON_KEYDOWN, 1L<<0, key_press, cub);
	mlx_hook(cub->data->win, ON_KEYUP, 1L<<1, key_release, cub);
	mlx_hook(cub->data->win, ON_DESTROY, 1L<<2, close_window, cub->data);
	mlx_loop_hook(cub->data->mlx, &key_move, cub);
	mlx_loop(cub->data->mlx);
	return (0);
}