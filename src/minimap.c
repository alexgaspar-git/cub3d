/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:02:24 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/09 17:24:15 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub)
{
	int	i = x;
	int j = y;
	
	cub->mini->m_ox = (cub->player->c_x - cub->player->p_x)/2;
	cub->mini->m_oy = (cub->player->c_y - cub->player->p_y)/2;
	while (i < cub->grid/2 + x)
	{
		j = y;
		while (j < cub->grid/2 + y)
		{
			if (i + cub->mini->m_ox < MW && j + cub->mini->m_oy < MH && i + cub->mini->m_ox >= 0 && j + cub->mini->m_oy  >= 0)
				my_mlx_pixel_put(cub->data, i + cub->mini->m_ox, j + cub->mini->m_oy, color);
			j++;
		}
		i++;
	}
}

void	dr_cone(t_cub *cub)
{
	int		i = 0;
	float	ang = cub->player->p_a - HALF_FOV;
	float	dx = cub->player->p_dx;
	float	dy = cub->player->p_dy;
	float	step = FOV / 50;

	while (i < 50)
	{
		dr_line(init_line(MW/2, MH/2, MW/2 + dx * 3, MH/2 + dy * 3, 0xAA343A40), cub);
		dx = cos(ang) * 5;
		dy = -sin(ang) * 5;
		ang += step;
		if (ang > PI2)
			ang -= PI2;
		i++;
	}
}

void	dr_player(t_cub *cub)
{
	int	i = 0;
	int j = 0;
	int	p_size = 8;

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
	dr_cone(cub);
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
			my_mlx_pixel_put(data, x, y, MMBG);
			x++;
		}
		y++;
	}
}

void	dr_minimap(char **map, t_cub *cub)
{
	int	player_x = (int)round_to_grid(cub->player->p_x)/64;
	int	player_y = (int)round_to_grid(cub->player->p_y)/64;
	int	x = player_x - 6;
	int	y = player_y - 6;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	minimap_bg(cub->data);
	while (y < cub->pars->y_max && y < player_y + 5)
	{
		x = player_x - 6;
		if (x < 0)
			x = 0;
		while (x < cub->pars->x_max && x < player_x + 8)
		{
			if (map[y][x] == '1')
				dr_square_mini(x * cub->grid/2 + cub->mini->p_mx, y * cub->grid/2 + cub->mini->p_my, 0xFFFFFF, cub);
			if (map[y][x] == 'P')
				dr_square_mini(x * cub->grid/2 + cub->mini->p_mx, y * cub->grid/2 + cub->mini->p_my, 0x827FD2, cub);
			if (map[y][x] == '0')
				dr_square_mini(x * cub->grid/2 + cub->mini->p_mx, y * cub->grid/2 + cub->mini->p_my, 0xAAAAAA, cub);
			if ((map[y][x] == 'N' || map[y][x] == 'E' ||  map[y][x] == 'S' || map[y][x] == 'W'))
				dr_square_mini(x * cub->grid/2 + cub->mini->p_mx, y * cub->grid/2 + cub->mini->p_my, 0x128EAF, cub);
			x++;
		}
		y++;
	}
	dr_player(cub);
	frame_map(cub);
}
