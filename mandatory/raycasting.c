/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:25:31 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/02 14:57:43 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by)));
}

void	get_line(t_cub *cub, t_ray *ray, float s_ang)
{
	ray->cam_a = cub->player->ang - s_ang;
	ray->dist *= cos(ray->cam_a);
	ray->line = (GRID * H) / ray->dist;
	ray->line_o = (H / 2) - ray->line / 2;
}

void	dr_render(t_cub *cub, t_ray ray, int i)
{
	int	bot;
	int	offset;

	offset = ray.line_o;
	bot = ray.line + ray.line_o;
	if (ray.dir == 0)
	{
		if (ray.ry < cub->player->y)
			dr_texture(init_line(i, offset, bot, 0xA6A6A6), cub, ray, NORTH);
		else
			dr_texture(init_line(i, offset, bot, 0xA6A6A6), cub, ray, SOUTH);
	}
	else
	{
		if (ray.rx < cub->player->x)
			dr_texture(init_line(i, offset, bot, 0xA6A6A6), cub, ray, WEST);
		else
			dr_texture(init_line(i, offset, bot, 0xA6A6A6), cub, ray, EAST);
	}
}

void	draw_rays(t_cub *cub)
{
	t_ray	ray;
	float	s_ang;
	int		i;

	s_ang = cub->player->ang + (PI / 6);
	if (s_ang > (PI * 2))
		s_ang -= (PI * 2);
	i = 0;
	while (i < W)
	{
		ray = get_ray(cub, s_ang);
		get_line(cub, &ray, s_ang);
		if (ray.line_o > 0)
			dr_line(init_line(i, 0, ray.line_o, cub->c), cub);
		dr_render(cub, ray, i);
		if (ray.line + ray.line_o < H)
			dr_line(init_line(i, ray.line + ray.line_o, H, cub->f), cub);
		s_ang -= ((PI / 3) / W);
		if (s_ang < 0)
			s_ang += (PI * 2);
		i++;
	}
}
