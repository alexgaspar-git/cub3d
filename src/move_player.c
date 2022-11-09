/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:51:49 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 18:13:12 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_angle(t_cub *cub)
{
	if (cub->key->left == 1)
	{
		cub->player->p_a += 0.05;
		if (cub->player->p_a > 2 * M_PI)
			cub->player->p_a = 0;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
	if (cub->key->right == 1)
	{
		cub->player->p_a -= 0.05;
		if (cub->player->p_a < 0)
			cub->player->p_a = 2 * M_PI;
		cub->player->p_dx = cos(cub->player->p_a) * 5;
		cub->player->p_dy = -sin(cub->player->p_a) * 5;
	}
}

void	move_player_front(t_cub *cub)
{
	if (cub->key->w == 1)
	{
		if (!is_wall_front(cub))
		{
			cub->player->p_x += cub->player->p_dx * cub->speed;
			cub->player->p_y += cub->player->p_dy * cub->speed;
		}
	}
	if (cub->key->s == 1)
	{
		if (!is_wall_behind(cub))
		{
			cub->player->p_x -= cub->player->p_dx * cub->speed;
			cub->player->p_y -= cub->player->p_dy * cub->speed;
		}
	}
}

void	move_player_side(t_cub *cub)
{
	if (cub->key->a == 1)
	{
		if (!is_wall_left(cub))
		{
			cub->player->p_x += cub->player->p_dy * cub->speed;
			cub->player->p_y -= cub->player->p_dx * cub->speed;
		}
	}
	if (cub->key->d == 1)
	{
		if (!is_wall_right(cub))
		{
			cub->player->p_x -= cub->player->p_dy * cub->speed;
			cub->player->p_y += cub->player->p_dx * cub->speed;
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
