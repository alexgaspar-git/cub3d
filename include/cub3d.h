/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:34:03 by algaspar          #+#    #+#             */
/*   Updated: 2022/10/18 16:33:21 by lide             ###   ########.fr       */
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
# include "../src/parsing/parsing.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTRm_oy = 17,
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

typedef struct s_mini
{
	int m_ox;
	int m_oy;
	int	p_mx;
	int p_my;
}	t_mini;

typedef struct s_player
{
	float p_x;
	float p_y;
	float p_dx;
	float p_dy;
	float p_a;
}	t_player;

typedef struct s_cub {
	t_data	*data;
	t_key	*key;
	t_parsing *pars;
	t_mini *mini;
	t_player *player;
	char	**map;
	int	grid;
	int	grid_gap;
}	t_cub;

void	dr_line(t_line line, t_cub *cub);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_data	*init_data(void);
t_cub	*init_cub(char **map);
void	*xalloc(size_t size);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		close_window(t_data *data);
void	init_hooks(t_cub *cub);
int		render(t_cub *cub);
void	find_player_mini(char **map, t_cub *cub);
void	frame_map(t_cub *cub);
void	move_map(t_cub *cub);
void	dr_square_mini(int x, int y, unsigned int color, t_cub *cub);
void	dr_player(t_cub *cub);
void	display_minimap(char **map, t_cub *cub);
t_line	init_line(int x1, int y1, int x2, int y2, int color);
#endif
