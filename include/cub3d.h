/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:34:03 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/13 18:23:05 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define W 1600
# define H 900
# define MW 400
# define MH 250
# define BG 0x424b52
# define border 0x0a3042

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_E = 14,
};

typedef struct s_line {
	int x1;
	int y1;
	int x2;
	int y2;
	int color;
}	t_line;

typedef struct s_bres
{
	int	ex;
	int	ey;
	int	dx;
	int	dy;
	int	xincr;
	int	yincr;
	int	cex;
	int	cey;
}	t_bres;

typedef struct s_draw
{
	int x;
	int y;
	int px;
}	t_draw;

typedef struct s_key {
	unsigned int w;
	unsigned int a;
	unsigned int s;
	unsigned int d;
	unsigned int q;
	unsigned int e;
}	t_key;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cub {
	t_data	*data;
	t_key	*key;
	char	**map;
	int ox;
	int oy;
	int playerx;
	int	playery;
	int	grid;
	int	grid_gap;
}	t_cub;

void	dr_line(t_line line, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data	*init_data(void);
t_cub	*init_cub(char **map);
void	*xalloc(size_t size);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		close_window(t_data *data);
void	init_hooks(t_cub *cub);
int		render(t_cub *cub);
void	find_player(char **map, t_cub *cub);
void	frame_map(t_cub *cub);

#endif