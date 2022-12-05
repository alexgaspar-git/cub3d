/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:51:49 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/05 14:16:46 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	move_player_angle(t_cub *cub)
{
	if (cub->key->left == 1)
	{
		cub->player->ang += 0.05;
		if (cub->player->ang > 2 * M_PI)
			cub->player->ang = 0;
		cub->player->dx = cos(cub->player->ang) * 5;
		cub->player->dy = -sin(cub->player->ang) * 5;
	}
	if (cub->key->right == 1)
	{
		cub->player->ang -= 0.05;
		if (cub->player->ang < 0)
			cub->player->ang = 2 * M_PI;
		cub->player->dx = cos(cub->player->ang) * 5;
		cub->player->dy = -sin(cub->player->ang) * 5;
	}
}

void	move_player_front(t_cub *cub)
{
	if (cub->key->w == 1)
	{
		if (!is_wall_front(cub))
		{
			cub->player->x += cub->player->dx * cub->speed;
			cub->player->y += cub->player->dy * cub->speed;
		}
	}
	if (cub->key->s == 1)
	{
		if (!is_wall_behind(cub))
		{
			cub->player->x -= cub->player->dx * cub->speed;
			cub->player->y -= cub->player->dy * cub->speed;
		}
	}
}

void	move_player_side(t_cub *cub)
{
	if (cub->key->a == 1)
	{
		if (!is_wall_left(cub))
		{
			cub->player->x += cub->player->dy * cub->speed;
			cub->player->y -= cub->player->dx * cub->speed;
		}
	}
	if (cub->key->d == 1)
	{
		if (!is_wall_right(cub))
		{
			cub->player->x -= cub->player->dy * cub->speed;
			cub->player->y += cub->player->dx * cub->speed;
		}
	}
}

void	move_player(t_cub *cub)
{
	if (cub->key->shift == 1)
		cub->speed = 2;
	move_player_front(cub);
	move_player_side(cub);
	move_player_angle(cub);
	cub->speed = 1;
}
