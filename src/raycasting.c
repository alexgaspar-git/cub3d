/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:25:31 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/27 19:51:33 by algaspar         ###   ########.fr       */
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
	if (ang > 0 && ang < PI)
	{
		ray.ry = round_to_grid(cub->player->p_y);
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
    int my = (int)ray.ry / GRID;
    if (sin(ang) < 0) {my -= ray.yo / GRID; }
	int mx;
	for (int i = 0; i < 8; i++) {
    	my += ray.yo / GRID;
    	mx = (int)ray.rx / GRID;
		if (is_wall(mx, my, cub)) { break; }
		ray.rx += ray.xo;
		ray.ry += ray.yo;
	}
	return (ray);
}

t_ray	cast_ver(t_cub *cub, float ang)
{
	t_ray	ray;

	ray = init_ray(ang);
	if (ang > HPI && ang < PI3)
	{
		ray.rx = round_to_grid(cub->player->p_x);
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
	int mx = (int)ray.rx / GRID;
    if (cos(ang) > 0) {mx -= ray.xo / GRID; }
	int my;
	for (int i = 0; i < 8; i++) {
    	mx += ray.xo / GRID;
    	my = (int)ray.ry / GRID;
		if (is_wall(mx, my, cub)) { break; }
		ray.rx += ray.xo;
		ray.ry += ray.yo;
	}
	return (ray);
}

float	calc_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
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



void	draw_rays(t_cub *cub)
{
	t_ray	ray;
	int		i;
	float	s_ang;
	float	dist;
	float	line;
	float 	lineO;
	float	cam_a;
	
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
		cam_a = cub->player->p_a - s_ang;
		dist = calc_dist(cub->player->p_x, cub->player->p_y, ray.rx, ray.ry);
		dist = dist * cos(cam_a);
		line = (GRID * 900)/dist;
		lineO = 450-line/2;
		// dr_line(init_line(cub->player->p_x, cub->player->p_y,
		// 		ray.rx, ray.ry, 0xAEFC02), cub);
		dr_line(init_line(i, lineO, i, line + lineO, 0xFF00FF), cub);
		i++;
	}
}
