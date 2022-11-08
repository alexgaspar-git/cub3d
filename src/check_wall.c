/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:04:44 by algaspar          #+#    #+#             */
/*   Updated: 2022/11/08 09:28:47 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
//doit gerer s + corner et aussi map quand pas de joueur

void	add_pixel(float *c, int key, int nb)
{
	if (!key)
		*c += nb;
	else
		*c -= nb;
}

void	move_pixel_n(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 10) / cub->grid);//5
	y4 = (int)((cub->player->p_y + 9) / cub->grid);//4
	x5 = (int)((cub->player->p_x - 10) / cub->grid);
	x4 = (int)((cub->player->p_x + 9) / cub->grid);
	if (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P')
	{
		if (cub->player->p_dy < -0.5 && (cub->map[y5][x] != '1' && cub->map[y5][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && (cub->map[y4][x] != '1' && cub->map[y4][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && (cub->map[y][x5] != '1' && cub->map[y][x5] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && (cub->map[y][x4] != '1' && cub->map[y][x4] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	move_pixel_s(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 10) / cub->grid);
	y4 = (int)((cub->player->p_y + 9) / cub->grid);
	x5 = (int)((cub->player->p_x - 10) / cub->grid);
	x4 = (int)((cub->player->p_x + 9) / cub->grid);
	if (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P')
	{
		if (cub->player->p_dy < -0.5 && (cub->map[y4][x] != '1' && cub->map[y4][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && (cub->map[y5][x] != '1' && cub->map[y5][x] != 'P'))
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && (cub->map[y][x4] != '1' && cub->map[y][x4] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && (cub->map[y][x5] != '1' && cub->map[y][x5] != 'P'))
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->p_x / cub->grid);
	y = (int)(cub->player->p_y / cub->grid);
	if (x > xf && (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P'))
		cub->player->p_x = ((xf + 1) * cub->grid) + 8;
	else if(x < xf && (cub->map[yf][x] != '1' && cub->map[yf][x] != 'P'))
		cub->player->p_x = (xf * cub->grid) - 9;
	else if (y > yf)
		cub->player->p_y = ((yf + 1) * cub->grid) + 8;
	else if(y < yf)
		cub->player->p_y = (yf * cub->grid) - 9;
	if (!cub->key->s)
		move_pixel_n(cub, yf, x, y);
	else
		move_pixel_s(cub, yf, x, y);
}


int	check_corner(t_cub *cub, int x, int y)
{
	int	xi;
	int	yi;

	xi = cub->player->p_x / cub->grid;
	yi = cub->player->p_y / cub->grid;
	if(cub->map[yi][x] == '1' || cub->map[y][xi] == '1' || cub->map[yi][x] == 'P' || cub->map[y][xi] == 'P')
	{
		if (!cub->key->s)
			move_pixel_n(cub, y, xi, yi);
		else
			move_pixel_s(cub, y, xi, yi);
		return (1);
	}
	return (0);
}

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x + cub->player->p_dx + 9) / cub->grid;// 4
	else
		x = (cub->player->p_x + cub->player->p_dx - 8) / cub->grid;// 3
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y + cub->player->p_dy + 9) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dy - 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_behind(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x - cub->player->p_dx - 9) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dx + 8) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y - cub->player->p_dy - 9) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dy + 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_left(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dy >= 0)
		x = (cub->player->p_x + cub->player->p_dy + 9) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dy - 8) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y - cub->player->p_dx - 9) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dx + 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

int	is_wall_right(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dy >= 0)
		x = (cub->player->p_x - cub->player->p_dy - 9) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dy + 8) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y + cub->player->p_dx + 9) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dx - 8) / cub->grid;
	if ((cub->map[y][x] == '1' || cub->map[y][x] == 'P'))
	{
		find_wall(cub, y, x);
		return (1);
	}
	if (check_corner(cub, x, y))
		return (1);
	return (0);
}

void	move_player(t_cub *cub)
{
	if (cub->key->w == 1)
	{
		if (!is_wall_front(cub))
		{
			cub->player->p_x += cub->player->p_dx;
			cub->player->p_y += cub->player->p_dy;
		}
	}
	if (cub->key->s == 1)
	{
		if (!is_wall_behind(cub))
		{
			cub->player->p_x -= cub->player->p_dx;
			cub->player->p_y -= cub->player->p_dy;
		}
	}
	if (cub->key->a == 1)
	{
		if (!is_wall_left(cub))
		{
			cub->player->p_x += cub->player->p_dy;
			cub->player->p_y -= cub->player->p_dx;
		}
	}
	if (cub->key->d == 1)
	{
		if (!is_wall_right(cub))
		{
			cub->player->p_x -= cub->player->p_dy;
			cub->player->p_y += cub->player->p_dx;
		}
	}
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