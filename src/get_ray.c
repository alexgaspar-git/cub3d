/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:44:35 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 15:12:43 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
		ray.ry = round_to_grid(cub->player->y);
		ray.rx = (cub->player->y - ray.ry) * -ray.a_tan + cub->player->x;
		ray.yo = -GRID;
		ray.xo = -ray.yo * -ray.a_tan;
	}
	else if (ang > PI && ang < (PI * 2))
	{
		ray.ry = round_to_grid(cub->player->y) + GRID;
		ray.rx = (cub->player->y - ray.ry) * -ray.a_tan + cub->player->x;
		ray.yo = GRID;
		ray.xo = -ray.yo * -ray.a_tan;
	}
	loop_hor(&ray, cub, ang);
	ray.dist = calc_dist(cub->player->x, cub->player->y, ray.rx, ray.ry);
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
	if (ang > (PI / 2) && ang < (3 * (PI / 2)))
	{
		ray.rx = round_to_grid(cub->player->x);
		ray.ry = (cub->player->x - ray.rx) * -ray.n_tan + cub->player->y;
		ray.xo = -GRID;
		ray.yo = -ray.xo * -ray.n_tan;
	}
	else if (ang < (PI / 2) || ang > (3 * (PI / 2)))
	{
		ray.rx = round_to_grid(cub->player->x) + GRID;
		ray.ry = (cub->player->x - ray.rx) * -ray.n_tan + cub->player->y;
		ray.xo = GRID;
		ray.yo = -ray.xo * -ray.n_tan;
	}
	loop_ver(&ray, cub, ang);
	ray.dist = calc_dist(cub->player->x, cub->player->y, ray.rx, ray.ry);
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
