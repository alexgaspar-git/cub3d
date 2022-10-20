/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:34:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/20 19:34:59 by algaspar         ###   ########.fr       */
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

void	check_horizontal(t_cub *cub)
{
	int	dof, mx, my;
	float rx, ry, ra, xo, yo, aTan;

	ra = cub->player->p_a;
	aTan = -1/tan(ra);
	rx = 0;
	ry = 0;
	dof = 0;
	xo = 0;
	yo = 0;
	if (ra > 0 + 0.05 && ra < M_PI - 0.05)
	{
		ry = ((int)(cub->player->p_y)/GRID) * GRID;
		rx = (cub->player->p_y - ry) * -aTan + cub->player->p_x;
		yo = -GRID;
		xo = -yo * -aTan;
	}
	else if (ra > M_PI + 0.05 && ra < 2 * M_PI - 0.05)
	{
		ry = (((int)(cub->player->p_y)/GRID) * GRID) + GRID;
		rx = (cub->player->p_y - ry) * -aTan + cub->player->p_x;
		yo = GRID;
		xo = -yo * -aTan;
	}
	else
	{
		rx = cub->player->p_x;
		ry = cub->player->p_y;
	}
	(void)mx;
	(void)my;
	while (dof < 8)
	{
		mx = (int)rx/GRID;
		my = (int)ry/GRID;
		if (mx > 0 && my > 0 && cub->map[my] && cub->map[my][mx] && cub->map[my][mx] == '1')
			break;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
			printf("map[%d][%d]| dof = %d\n", my, mx, dof);
		}
	}
	t_line line = init_line(cub->player->p_x, cub->player->p_y, rx, ry, 0xFF0000);
	dr_line(line, cub);
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
	printf("p_x: %f | p_y: %f | p_dx: %f | p_dy: %f | p_a: %f\n", cub->player->p_x, cub->player->p_y, cub->player->p_dx, cub->player->p_dy, cub->player->p_a);
	// printf("on tile: [%d,%d]\n", (int)roundf(cub->player->p_x/64 - 0.5), (int)roundf(cub->player->p_y/64 - 0.5));
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
