/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:44:35 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/12 18:15:14 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	loop_hor(t_ray *ray, t_cub *cub, float ang)
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

static t_ray	cast_hor(t_cub *cub, float ang)
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
	ray.dist = calc_dist(cub->player->p_x, cub->player->p_y, ray.rx, ray.ry);
	return (ray);
}

static void	loop_ver(t_ray *ray, t_cub *cub, float ang)
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

static t_ray	cast_ver(t_cub *cub, float ang)
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
	ray.dist = calc_dist(cub->player->p_x, cub->player->p_y, ray.rx, ray.ry);
	return (ray);
}

t_ray	get_ray(t_cub *cub, float ang)
{
	t_ray		hor;
	t_ray		ver;

	hor = cast_hor(cub, ang);
	ver = cast_ver(cub, ang);
	if (hor.dist < ver.dist)
		return (hor);
	else
		return (ver);
}
