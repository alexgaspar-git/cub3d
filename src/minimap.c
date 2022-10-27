/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:02:24 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/28 00:16:35 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_map(t_cub *cub)
{
	if (cub->key->w == 1)
		cub->mini->m_oy += 2;
	if (cub->key->a == 1)
		cub->mini->m_ox += 2;
	if (cub->key->s == 1)
		cub->mini->m_oy -= 2;
	if (cub->key->d == 1)
		cub->mini->m_ox -= 2;
}

void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (i + cub->mini->m_ox < MW && j + cub->mini->m_oy < MH && i + cub->mini->m_ox >= 0 && j + cub->mini->m_oy >= 0)
				my_mlx_pixel_put(cub->data, i + cub->mini->m_ox, j + cub->mini->m_oy, color);
			j++;
		}
		i++;
	}
}

void	dr_player(t_cub *cub)
{
	int	i = 0;
	int j = 0;
	int	p_size = 6;

	while (i < p_size)
	{
		j = 0;
		while (j < p_size)
		{
			my_mlx_pixel_put(cub->data, i + MW/2 - (p_size/2), j + MH/2 - (p_size/2) , 0x0000FF);
			j++;
		}
		i++;
	}
}

void	display_minimap(char **map, t_cub *cub)
{
	int	x = 0;
	int	y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				dr_square_mini(x * (cub->grid) + cub->mini->p_mx, y * (cub->grid) + cub->mini->p_my, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square_mini(x * (cub->grid) + cub->mini->p_mx, y * (cub->grid) + cub->mini->p_my, 0xAAAAAA, cub);
			if ( map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square_mini(x * (cub->grid) + cub->mini->p_mx, y * (cub->grid) + cub->mini->p_my, 0xFF0000, cub);
			x++;
		}
		y++;
	}
	frame_map(cub);
}

void	find_player_mini(char **map, t_cub *cub)
{
	int	x;
	int y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
			{
				cub->mini->p_mx = MW / 2 - x * cub->grid - (cub->grid/2);
				cub->mini->p_my = MH / 2 - y * cub->grid - (cub->grid/2);
				return ;
			}
			x++;
		}
		y++;
	}
}
