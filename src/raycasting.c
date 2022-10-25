/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:25:31 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/25 19:45:46 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	init_ray(float ang)
{
	t_ray	ray;

	ray.rx = 100000;
	ray.ry = 100000;
	ray.xo = 0;
	ray.yo = 0;
	ray.aTan = -1 / tan(ang);
	ray.nTan = -tan(ang);
	return (ray);
}

float	round_to_grid(float pos)
{
	return (((int)pos / GRID) * GRID);
}

int	is_wall(int mx, int my, t_cub *cub)
{
	if (mx < cub->pars->x_max && my < cub->pars->y_max
		&& mx >= 0 && my >= 0 && cub->map[my]
		&& cub->map[my][mx] && cub->map[my][mx] == '1')
		return (1);
	else
		return (0);
}

void	cast_loop(t_ray *ray, t_cub *cub)
{
	int	dof;
	int	mx;
	int	my;

	dof = 0;
	while (dof < 8)
	{
		mx = (int)ray->rx / GRID;
		my = (int)ray->ry / GRID;
		if (is_wall(mx, my, cub))
			break ;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			dof++;
		}
	}
}

t_ray	cast_hor(t_cub *cub, float ang)
{
	t_ray	ray;

	ray = init_ray(ang);
	if (ray.aTan > 20 || ray.aTan < -20)
		return (ray);
	if (ang > 0 && ang < PI)
	{
		ray.ry = round_to_grid(cub->player->p_y) - 1;
		ray.rx = (cub->player->p_y - ray.ry) * -ray.aTan + cub->player->p_x;
		ray.yo = -GRID;
		ray.xo = -ray.yo * -ray.aTan;
	}
	else if (ang > PI && ang < PI2)
	{
		ray.ry = round_to_grid(cub->player->p_y) + GRID;
		ray.rx = (cub->player->p_y - ray.ry) * -ray.aTan + cub->player->p_x;
		ray.yo = GRID;
		ray.xo = -ray.yo * -ray.aTan;
	}
	cast_loop(&ray, cub);
	return (ray);
}

t_ray	cast_ver(t_cub *cub, float ang)
{
	t_ray	ray;

	ray = init_ray(ang);
	if (ang > HPI && ang < PI3)
	{
		ray.rx = round_to_grid(cub->player->p_x) - 1;
		ray.ry = (cub->player->p_x - ray.rx) * -ray.nTan + cub->player->p_y;
		ray.xo = -GRID;
		ray.yo = -ray.xo * -ray.nTan;
	}
	else if (ang < HPI || ang > PI3)
	{
		ray.rx = round_to_grid(cub->player->p_x) + GRID;
		ray.ry = (cub->player->p_x - ray.rx) * -ray.nTan + cub->player->p_y;
		ray.xo = GRID;
		ray.yo = -ray.xo * -ray.nTan;
	}
	cast_loop(&ray, cub);
	return (ray);
}

float	calc_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

t_ray	get_ray(t_cub *cub, float ang)
{
	t_ray		hor;
	t_ray		ver;
	t_player	*p;

	hor = cast_hor(cub, ang);
	ver = cast_ver(cub, ang);
	p = cub->player;
	if (calc_dist(p->p_x, p->p_y, ver.rx, ver.ry)
		> calc_dist(p->p_x, p->p_y, hor.rx, hor.ry))
		return (hor);
	else
		return (ver);
}

void	draw_rays2(t_cub *cub)
{
	t_ray	ray;
	int		i;
	float	s_ang;

	s_ang = cub->player->p_a - HALF_FOV;
	if (s_ang < 0)
		s_ang += PI2;
	i = 0;
	while (i < CASTED_RAYS)
	{
		ray = get_ray(cub, s_ang);
		s_ang += STEP_ANGLE;
		if (s_ang > PI2)
			s_ang -= PI2;
		dr_line(init_line(cub->player->p_x, cub->player->p_y,
				ray.rx, ray.ry, 0xAEFC02), cub);
		i++;
	}
}

void	draw_single_ray(t_cub *cub)
{
	t_ray	ray;
	
	ray = get_ray(cub, cub->player->p_a);
	dr_line(init_line(cub->player->p_x, cub->player->p_y,
			ray.rx, ray.ry, 0xAEFC02), cub);
}

////////////////////////////////////////////////////////

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
		if (ra > 0 && ra < M_PI)
			my -= 1;
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
	if (ra > M_PI && ra < 2 * M_PI)
		ray.ry = ry - 1;
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
		if (ra > (M_PI / 2) && ra < (3 * (M_PI / 2)))
			mx -= 1;
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
	if (ra < (M_PI / 2) || ra > (3 * (M_PI / 2)))
		ray.rx = rx - 1;
	ray.ry = ry;
	return (ray);
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