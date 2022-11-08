/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:02:24 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/08 09:14:58 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;

	while (i < cub->grid + x)
	{
		j = y;
		while (j < cub->grid + y)
		{
			if (i + cub->mini->m_ox < MW && j + cub->mini->m_oy < MH && i + cub->mini->m_ox >= 0 && j + cub->mini->m_oy  >= 0)
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
	int	p_size = 16;

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
	dr_line(init_line(MW/2, MH/2, MW/2 + cub->player->p_dx * 10, MH/2 + cub->player->p_dy * 10, 0xFF00FF), cub);
}

void minimap_bg(t_data *data)
{
	int	x = 0;
	int	y = 0;

	while (y < MH)
	{
		x = 0;
		while (x < MW)
		{
			my_mlx_pixel_put(data, x, y, BG);
			x++;
		}
		y++;
	}
}

void	display_minimap(char **map, t_cub *cub)
{
	int	x = 0;
	int	y = 0;

	minimap_bg(cub->data);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1' || map[y][x] == 'P')
				dr_square_mini(x * cub->grid + cub->mini->p_mx, y * cub->grid + cub->mini->p_my, 0xFFFFFF, cub);
			if (map[y][x] == '0')
				dr_square_mini(x * cub->grid + cub->mini->p_mx, y * cub->grid + cub->mini->p_my, 0xAAAAAA, cub);
			if ( map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W')
				dr_square_mini(x * cub->grid + cub->mini->p_mx, y * (cub->grid) + cub->mini->p_my, 0x128EAF, cub);
			x++;
		}
		y++;
	}
	dr_player(cub);
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
				cub->mini->p_mx = MW / 2 - x * cub->grid - (cub->grid / 2);
				cub->mini->p_my = MH / 2 - y * cub->grid - (cub->grid / 2);
				return ;
			}
			x++;
		}
		y++;
	}
}
