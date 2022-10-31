/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:21:45 by lide              #+#    #+#             */
/*   Updated: 2022/10/31 18:26:33 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_texel_color(t_tex *txt, int x, int y)
{
	int		color;
	char	*dst;

	dst = txt->addr + (y * txt->line_length + x * (txt->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

init_tex(t_data *data ,t_tex *tex, char *direction)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, direction, &tex->w, &tex->h);
}

t_tex	*get_texture(t_data *data, t_parsing *parsing)
{
	t_tex	*tex;

	tex = malloc(sizeof (t_tex) * 4);
	init_tex(data, &tex[0], parsing->no);
}
