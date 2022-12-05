/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:34:03 by algaspar          #+#    #+#             */
/*   Updated: 2022/12/05 15:15:48 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define W 1400
# define H 1120
# define MW 350
# define MH 280
# define MMBG 0x0A0A0A
# define BORDER 0x0a3042
# define PI M_PI
# define GRID 64
# define NORTH 0
# define WEST 1
# define SOUTH 2
# define EAST 3
# define DOF 1000

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "../mandatory/parsing/parsing.h"

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
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
};

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_line {
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	color;
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
	int	x;
	int	y;
	int	px;
}	t_draw;

typedef struct s_key {
	unsigned int	w;
	unsigned int	a;
	unsigned int	s;
	unsigned int	d;
	unsigned int	left;
	unsigned int	right;
	unsigned int	shift;
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

typedef struct s_tex {
	void	*img;
	char	*addr;
	int		w;
	int		h;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_ray
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	a_tan;
	float	n_tan;
	int		dir;
	float	dist;
	float	line;
	float	line_o;
	float	cam_a;
}	t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	ang;
	float	cx;
	float	cy;
	int		mx;
	int		my;
}	t_player;

typedef struct s_cub {
	t_data			*data;
	t_key			*key;
	t_parsing		*pars;
	t_player		*player;
	char			**map;
	unsigned int	f;
	unsigned int	c;
	unsigned int	speed;
	t_tex			*tex;
}					t_cub;

void	add_pixel(float *c, int key, int nb);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dr_line(t_line line, t_cub *cub);
void	dr_square(int x, int y, unsigned int color, t_cub *cub);
void	move_player(t_cub *cub);
void	draw_rays(t_cub *cub);
t_ray	get_ray(t_cub *cub, float ang);

//utils
float	round_to_grid(float pos);
int		ft_abs(int x);
void	get_dir(char pos, t_player *player);
void	get_player(char **map, t_player *player);
float	calc_dist(float ax, float ay, float bx, float by);
void	draw_bg(t_cub *cub);
int		is_wall(int mx, int my, t_cub *cub);

//hooks
int		render(t_cub *cub);
int		key_press(int keycode, t_cub *cub);
int		key_release(int keycode, t_cub *cub);
int		close_window(t_cub *cub);

//init
t_cub	*init_cub(char **map);
t_line	init_line_x(t_point a, t_point b, unsigned int color);
t_line	init_line(int x1, int y1, int y2, int color);
t_point	init_point(int x, int y);
void	init_hooks(t_cub *cub);
t_ray	init_ray(float ang);

//check wall
int		check_corner(t_cub *cub, int x, int y);
void	find_wall(t_cub *cub, int yf, int xf);
int		is_wall_right(t_cub *cub);
int		is_wall_left(t_cub *cub);
int		is_wall_behind(t_cub *cub);
int		is_wall_front(t_cub *cub);

//texture
t_tex	*get_texture(t_data *data, t_parsing *parsing);
int		get_texel_color(t_tex *txt, int x, int y);
void	dr_texture(t_line line, t_cub *cub, t_ray ray, int i);

#endif
