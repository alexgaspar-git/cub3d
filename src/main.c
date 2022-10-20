/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:38 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/20 18:47:17 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_window(t_data *data)
{
	int	x = 0;
	int	y = 0;

	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			my_mlx_pixel_put(data, x, y, BG);
			x++;
		}
		y++;
	}
}

//commente les dr_line si tu veux isoler une ligner pour tester

void	check_horizontal(t_cub *cub)
{
	float ynearest = 0;
	float xnearest = 0;

	if (cub->player->p_a > 0 && cub->player->p_a < M_PI)
	{
		ynearest = cub->player->p_y - ((int)(cub->player->p_y)/GRID) * GRID;
		xnearest = ynearest/tan(cub->player->p_a);
		//ligne jaune qui check les intersections horizontales que dans la moitié haut du rayon (entre 0 et 180 degrés)
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + xnearest, cub->player->p_y - ynearest, 0xFFFF00), cub);
	}
	else if (cub->player->p_a > M_PI && cub->player->p_a <= 2 * M_PI)
	{
		ynearest = cub->player->p_y - ((int)(cub->player->p_y)/GRID) * GRID;
		xnearest = ynearest/tan(cub->player->p_a);
		//ligne rouge moitié bas
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x - xnearest, cub->player->p_y + ynearest, 0xFF0000), cub);
	}
	else if (cub->player->p_a == 0 || cub->player->p_a == M_PI)
	{
		ynearest = cub->player->p_y;
		xnearest = cub->player->p_x;
	}
}

void	check_vertical(t_cub *cub)
{
	float ynearest = 0;
	float xnearest = 0;

	if (cub->player->p_a > M_PI_2 && cub->player->p_a < 3 * M_PI_2)
	{
		xnearest = cub->player->p_y - ((int)(cub->player->p_y)/GRID) * GRID;
		ynearest = xnearest * tan(cub->player->p_a);
		//ligne verte intersection verticales côté gauche
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x - xnearest, cub->player->p_y + ynearest, 0x00FF00), cub);
	}
	else if (cub->player->p_a < M_PI_2 || cub->player->p_a > 3 * M_PI_2)
	{
		xnearest = cub->player->p_y - ((int)(cub->player->p_y)/GRID) * GRID;
		ynearest = xnearest * tan(cub->player->p_a);
		//ligne bleu ciel côté droit
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + xnearest, cub->player->p_y - ynearest, 0x00FFFF), cub);
	}
	else if (cub->player->p_a == M_PI_2 || cub->player->p_a == 3 * M_PI_2)
	{
		ynearest = cub->player->p_y;
		xnearest = cub->player->p_x;
	}
}

void	draw_rays(t_cub *cub)
{
	float	start_a = cub->player->p_a - HALF_FOV;
	int	i = 0;

	while (i < CASTED_RAYS)
	{
		dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cos(start_a) * 500, cub->player->p_y + -sin(start_a) * 500, 0xFFFFFF), cub);
		start_a += STEP_ANGLE;
		i++;
	}
}

int	render(t_cub *cub)
{
	move_player(cub);
	draw_map(cub->map, cub);
	draw_player(cub);
	// draw_rays(cub);
	check_horizontal(cub);
	check_vertical(cub);
	// printf("p_x: %f | p_y: %f | p_dx: %f | p_dy: %f | p_a: %f\n", cub->player->p_x, cub->player->p_y, cub->player->p_dx, cub->player->p_dy, cub->player->p_a);
	// printf("on tile: [%f,%f]\n", roundf(cub->player->p_x/64 - 0.5), roundf(cub->player->p_y/64 - 0.5));
	// dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cub->player->p_dx * 20,  cub->player->p_y + cub->player->p_dy * 20, 0xFF00FF), cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	clear_window(cub->data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub *cub;

	if (argc < 2)
	{
		printf("cub3d needs a map\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		printf("too many arguments\n");
		exit(EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		exit(EXIT_FAILURE);
	cub = init_cub(argv);
	init_hooks(cub);
	free_list(cub->pars->mlc);
	return (0);
}
