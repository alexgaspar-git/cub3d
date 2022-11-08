/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:25:31 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/08 19:14:44 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_ray	init_ray(float ang)
{
	t_ray	ray;

	ray.rx = 100000;
	ray.ry = 100000;
	ray.xo = 0;
	ray.yo = 0;
	ray.aTan = -1 / tan(ang);
	ray.nTan = -tan(ang);
	ray.dir = 0;
	return (ray);
}

float	round_to_grid(float pos)
{
	return (((int)pos / GRID) * GRID);
}

int	is_wall(int mx, int my, t_cub *cub)
{
	return (mx < cub->pars->x_max && my < cub->pars->y_max
		&& mx >= 0 && my >= 0 && cub->map[my]
		&& cub->map[my][mx] && (cub->map[my][mx] == '1' || cub->map[my][mx] == 'P'));
}

void	loop_hor(t_ray *ray, t_cub *cub, float ang)
{
	int	mx;
	int	my;
	int	i;

	my = (int)ray->ry / GRID;
    if (sin(ang) < 0)
		my -= ray->yo / GRID;
	i = 0;
	while (i < DOF)
	{
		mx = (int)ray->rx / GRID;
		my += ray->yo / GRID;
		if (is_wall(mx, my, cub))
			break ;
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		i++;
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
	loop_hor(&ray, cub, ang);
	return (ray);
}

void	loop_ver(t_ray *ray, t_cub *cub, float ang)
{
	int	mx;
	int	my;
	int	i;

	mx = (int)ray->rx / GRID;
    if (cos(ang) > 0)
		mx -= ray->xo / GRID;
	i = 0;
	while (i < DOF)
	{
		mx += ray->xo / GRID;
		my = (int)ray->ry / GRID;
		if (is_wall(mx, my, cub))
			break ;
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		i++;
	}
}

t_ray	cast_ver(t_cub *cub, float ang)
{
	t_ray	ray;

	ray = init_ray(ang);
	ray.dir = 1;
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
	loop_ver(&ray, cub, ang);
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

int	check_door(float ry, float rx, char **map)
{
	int	y;
	int	x;
	int	y2;
	int	x2;

	y = (int)(ry/GRID);
	y2 = (int)((ry - 1)/GRID);
	x = (int)(rx/GRID);
	x2 = (int)((rx - 1)/GRID);
	if (map[y][x] == 'P')
		return (1);
	else if (map[y2] && map[y][x2] && (map[y][x] == 'P'
		|| map[y2][x] == 'P' || map[y][x2] == 'P'))
		return (1);
	return (0);
}

void	draw_rays(t_cub *cub)
{
	t_ray	ray;// j'ai besoin de ray
	int		i;
	float	s_ang;
	float	dist;
	float	line;
	float 	line_o;
	float	cam_a;

	s_ang = cub->player->p_a + HALF_FOV;
	if (s_ang > PI2)
		s_ang -= PI2;
	i = 0;
	while (i < CASTED_RAYS)
	{
		ray = get_ray(cub, s_ang);
		cam_a = cub->player->p_a - s_ang;
		dist = calc_dist(cub->player->p_x, cub->player->p_y, ray.rx, ray.ry);
		dist *= cos(cam_a);
		line = (GRID * H)/dist;
		line_o = (H / 2) - line / 2;
		if (check_door(ray.ry, ray.rx, cub->map))
			dr_texture(init_line(i, line_o, i, line + line_o, 0xA6A6A6), cub, ray , DOOR);
		else if (ray.dir == 0)
		{
			if (ray.ry < cub->player->p_y)
				dr_texture(init_line(i, line_o, i, line + line_o, 0xA6A6A6), cub, ray , NORTH);//hor
			else if (ray.ry > cub->player->p_y)
				dr_texture(init_line(i, line_o, i, line + line_o, 0xA6A6A6), cub, ray , SOUTH);//hor
		}
		else
		{
			if (ray.rx < cub->player->p_x)
				dr_texture(init_line(i, line_o, i, line + line_o, 0xA6A6A6), cub, ray, WEST);//ver
			else if (ray.rx > cub->player->p_x)
				dr_texture(init_line(i, line_o, i, line + line_o, 0xA6A6A6), cub, ray, EAST);//ver
		}
		s_ang -= STEP_ANGLE;
		if (s_ang < 0)
			s_ang += PI2;
		i++;
	}
}
