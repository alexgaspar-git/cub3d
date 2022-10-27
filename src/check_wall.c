/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:04:44 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/27 22:24:47 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//doit gerer s + corner et aussi map quand pas de joueur

void	add_pixel(float *c, int key, int nb)
{
	if (!key)
		*c += nb;
	else
		*c -= nb;
}

// void	find_wall(t_cub *cub, int yf, int xf)
// {
// 	int	x;
// 	int	y;

// 	x = (int)(cub->player->p_x / cub->grid);
// 	y = (int)(cub->player->p_y / cub->grid);
// 	if (x > xf && cub->map[yf][x] != '1'/*!= 0 && yf != cub->pars->y_max - 1*/)
// 	{
// 		cub->player->p_x = ((xf + 1) * cub->grid) + 3;
// 		if (cub->player->p_dy < -0.5 && cub->map[(int)((cub->player->p_y - 5) / cub->grid)][(int)((cub->player->p_x) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_y), cub->key->s, -1);
// 			// cub->player->p_y -= 1;
// 		else if (cub->player->p_dy > 0.5 && cub->map[(int)((cub->player->p_y + 4) / cub->grid)][(int)((cub->player->p_x) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_y), cub->key->s, 1);
// 			// cub->player->p_y += 1;
// 		// printf("1 yf %d | y %d  xf %d | x %d\n", yf, y, xf, x);
// 	}
// 	else if(x < xf && cub->map[yf][x] != '1'/*yf != 0 && yf != cub->pars->y_max - 1*/)
// 	{
// 		cub->player->p_x = (xf * cub->grid) - 4;
// 		if (cub->player->p_dy < -0.5 && cub->map[(int)((cub->player->p_y - 5) / cub->grid)][(int)((cub->player->p_x) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_y), cub->key->s, -1);
// 			// cub->player->p_y -= 1;
// 		else if (cub->player->p_dy > 0.5 && cub->map[(int)((cub->player->p_y + 4) / cub->grid)][(int)((cub->player->p_x) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_y), cub->key->s, 1);
// 			// cub->player->p_y += 1;
// 		// printf("2 yf %d | y %d  xf %d | x %d\n", yf, y, xf, x);
// 	}
// 	else if (y > yf)
// 	{
// 		cub->player->p_y = ((yf + 1) * cub->grid) + 3;
// 		if (cub->player->p_dx < -0.5 && cub->map[(int)((cub->player->p_y) / cub->grid)][(int)((cub->player->p_x - 5) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_x), cub->key->s, -1);
// 			// cub->player->p_x -= 1;
// 		else if (cub->player->p_dx > 0.5 && cub->map[(int)((cub->player->p_y) / cub->grid)][(int)((cub->player->p_x + 4) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_x), cub->key->s, 1);
// 			// cub->player->p_x += 1;
// 		// printf("3 yf %d | y %d  xf %d | x %d\n", yf, y, xf, x);
// 	}
// 	else if(y < yf)
// 	{
// 		cub->player->p_y = (yf * cub->grid) - 4;
// 		if (cub->player->p_dx < -0.5 && cub->map[(int)((cub->player->p_y) / cub->grid)][(int)((cub->player->p_x - 5) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_x), cub->key->s, -1);
// 			// cub->player->p_x -= 1;
// 		else if (cub->player->p_dx > 0.5 && cub->map[(int)((cub->player->p_y) / cub->grid)][(int)((cub->player->p_x + 4) / cub->grid)] != '1')
// 			add_pixel(&(cub->player->p_x), cub->key->s, 1);
// 			// cub->player->p_x += 1;
// 		// printf("4 yf %d | y %d  xf %d | x %d\n", yf, y, xf, x);
// 	}
// 	// printf("dx|dy %f|%f\n", cub->player->p_dx, cub->player->p_dy);
// }

void	move_pixel_n(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 5) / cub->grid);
	y4 = (int)((cub->player->p_y + 4) / cub->grid);
	x5 = (int)((cub->player->p_x - 5) / cub->grid);
	x4 = (int)((cub->player->p_x + 4) / cub->grid);
	if (cub->map[yf][x] != '1')
	{
		if (cub->player->p_dy < -0.5 && cub->map[y5][x] != '1')
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && cub->map[y4][x] != '1')
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && cub->map[y][x5] != '1')
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && cub->map[y][x4] != '1')
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	move_pixel_s(t_cub *cub, int yf, int x, int y)
{
	int	y5;
	int	y4;
	int	x5;
	int	x4;

	y5 = (int)((cub->player->p_y - 5) / cub->grid);
	y4 = (int)((cub->player->p_y + 4) / cub->grid);
	x5 = (int)((cub->player->p_x - 5) / cub->grid);
	x4 = (int)((cub->player->p_x + 4) / cub->grid);
	if (cub->map[yf][x] != '1')
	{
		if (cub->player->p_dy < -0.5 && cub->map[y4][x] != '1')
			add_pixel(&(cub->player->p_y), cub->key->s, -1);
		else if (cub->player->p_dy > 0.5 && cub->map[y5][x] != '1')
			add_pixel(&(cub->player->p_y), cub->key->s, 1);
	}
	else
	{
		if (cub->player->p_dx < -0.5 && cub->map[y][x4] != '1')
			add_pixel(&(cub->player->p_x), cub->key->s, -1);
		else if (cub->player->p_dx > 0.5 && cub->map[y][x5] != '1')
			add_pixel(&(cub->player->p_x), cub->key->s, 1);
	}
}

void	find_wall(t_cub *cub, int yf, int xf)
{
	int	x;
	int	y;

	x = (int)(cub->player->p_x / cub->grid);
	y = (int)(cub->player->p_y / cub->grid);
	if (x > xf && cub->map[yf][x] != '1')
		cub->player->p_x = ((xf + 1) * cub->grid) + 3;
	else if(x < xf && cub->map[yf][x] != '1')
		cub->player->p_x = (xf * cub->grid) - 4;
	else if (y > yf)
		cub->player->p_y = ((yf + 1) * cub->grid) + 3;
	else if(y < yf)
		cub->player->p_y = (yf * cub->grid) - 4;
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
	if(cub->map[yi][x] == '1' || cub->map[y][xi] == '1')
		return (1);
	return (0);
}

int	is_wall_front(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->player->p_dx >= 0)
		x = (cub->player->p_x + cub->player->p_dx + 4) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dx - 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y + cub->player->p_dy + 4) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dy - 3) / cub->grid;
	if (cub->map[y][x] == '1')
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
		x = (cub->player->p_x - cub->player->p_dx - 4) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dx + 3) / cub->grid;
	if (cub->player->p_dy >= 0)
		y = (cub->player->p_y - cub->player->p_dy - 4) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dy + 3) / cub->grid;
	if (cub->map[y][x] == '1')
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
		x = (cub->player->p_x + cub->player->p_dy + 4) / cub->grid;
	else
		x = (cub->player->p_x + cub->player->p_dy - 3) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y - cub->player->p_dx - 4) / cub->grid;
	else
		y = (cub->player->p_y - cub->player->p_dx + 3) / cub->grid;
	if (cub->map[y][x] == '1')
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
		x = (cub->player->p_x - cub->player->p_dy - 4) / cub->grid;
	else
		x = (cub->player->p_x - cub->player->p_dy + 3) / cub->grid;
	if (cub->player->p_dx >= 0)
		y = (cub->player->p_y + cub->player->p_dx + 4) / cub->grid;
	else
		y = (cub->player->p_y + cub->player->p_dx - 3) / cub->grid;
	if (cub->map[y][x] == '1')
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
