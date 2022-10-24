/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:34:57 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/24 20:00:57 by lide             ###   ########.fr       */
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

t_ray	check_horizontal(t_cub *cub, float ra)
{
	int	dof, mx, my;
	float rx, ry, xo, yo, aTan;
	t_ray ray;

	ray.rx = 99999999;
	ray.ry = 99999999;
	dof = 0;
	aTan = -1/tan(ra);
	if (aTan > 20 || aTan < -20)
		return (ray);
	if (ra > 0 && ra < M_PI)
	{
		ry = ((int)(cub->player->p_y)/GRID) * GRID;
		rx = (cub->player->p_y - ry) * -aTan + cub->player->p_x;
		yo = -GRID;
		xo = -yo * -aTan;
	}
	else if (ra > M_PI && ra < 2 * M_PI)
	{
		ry = (((int)(cub->player->p_y)/GRID) * GRID) + GRID;
		rx = (cub->player->p_y - ry) * -aTan + cub->player->p_x;
		yo = GRID;
		xo = -yo * -aTan;
	}
	else if (ra == 0 || ra == 3.14)
	{
		rx = 100000;
		ry = 100000;
		dof = 8;
	}
	(void)mx;
	(void)my;
	while (dof < 8)
	{
		mx = (int)rx/GRID;
		my = (int)ry/GRID;
		if (mx < cub->pars->x_max && my < cub->pars->y_max && mx >= 0 && my >= 0 && cub->map[my] && cub->map[my][mx] && cub->map[my][mx] == '1')
			break;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	ray.rx = rx;
	ray.ry = ry;
	return (ray);
}

t_ray	check_vertical(t_cub *cub, float ra)
{
	int	dof, mx, my;
	float rx, ry, xo, yo, nTan;

	nTan = -tan(ra);
	dof = 0;
	if (ra > (M_PI / 2) && ra < (3 * (M_PI / 2)))
	{
		rx = ((int)(cub->player->p_x)/GRID) * GRID;
		ry = (cub->player->p_x - rx) * -nTan + cub->player->p_y;
		xo = -GRID;
		yo = -xo * -nTan;
	}
	else if (ra < (M_PI / 2) || ra > (3 * (M_PI / 2)))
	{
		rx = (((int)(cub->player->p_x)/GRID) * GRID) + GRID;
		ry = (cub->player->p_x - rx) * -nTan + cub->player->p_y;
		xo = GRID;
		yo = -xo * -nTan;
	}
	else
	{
		rx = 99999999;
		ry = 99999999;
	}
	while (dof < 8)
	{
		mx = (int)rx/GRID;
		my = (int)ry/GRID;
		if (mx <= cub->pars->x_max && my <= cub->pars->y_max && mx >= 0 && my >= 0 && cub->map[my] && cub->map[my][mx] && cub->map[my][mx] == '1')
			break;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	t_ray ray;
	ray.rx = rx;
	ray.ry = ry;
	return (ray);
}

float	calc_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax)*(bx - ax)+(by-ay)*(by-ay)));
}

t_ray	comp_dist(t_ray ver, t_ray hor, t_cub *cub)
{
	float distV;
	float distH;

	distV = calc_dist(cub->player->p_x, cub->player->p_y, ver.rx, ver.ry);
	distH = calc_dist(cub->player->p_x, cub->player->p_y, hor.rx, hor.ry);
	if (distV >= distH)
		return (hor);
	else
		return (ver);
}

void	draw_rays(t_cub *cub)
{
	t_ray	ver;
	t_ray	hor;
	t_ray	final;
	int	i = 0;
	float	start_a = cub->player->p_a - HALF_FOV;
	if (start_a < 0)
		start_a += (2*M_PI);


	while (i < CASTED_RAYS)
	{
		ver = check_vertical(cub, start_a);
		hor = check_horizontal(cub, start_a);
		final = comp_dist(ver, hor, cub);
		start_a += STEP_ANGLE;
		if (start_a > 2*M_PI)
			start_a -= 2*M_PI;
		dr_line(init_line(cub->player->p_x, cub->player->p_y, final.rx, final.ry, 0xAEFC02), cub);
		i++;
	}
}

int	render(t_cub *cub)
{
	move_player(cub);
	draw_map(cub->map, cub);
	draw_player(cub);
	draw_rays(cub);
	dr_line(init_line(cub->player->p_x, cub->player->p_y, cub->player->p_x + cub->player->p_dx * 20,  cub->player->p_y + cub->player->p_dy * 20, 0xFF00FF), cub);
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
