/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_dir_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:38:40 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/05 14:16:38 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_dir(char pos, t_player *player)
{
	if (pos == 'N')
		player->ang = (PI / 2);
	else if (pos == 'E')
		player->ang = 0;
	else if (pos == 'S')
		player->ang = (3 * (PI / 2));
	else
		player->ang = PI;
}

void	get_player(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E'
				|| map[y][x] == 'S' || map[y][x] == 'W')
			{
				player->x = x * GRID + (GRID / 2);
				player->y = y * GRID + (GRID / 2);
				player->mx = MW / 2 - x * GRID / 2 - (GRID / 4);
				player->my = MH / 2 - y * GRID / 2 - (GRID / 4);
				get_dir(map[y][x], player);
				return ;
			}
			x++;
		}
		y++;
	}
}
