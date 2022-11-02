/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:21:45 by lide              #+#    #+#             */
/*   Updated: 2022/11/02 16:10:48 by lide             ###   ########.fr       */
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

void	init_tex(t_data *data ,t_tex *tex, char *direction, t_list *mlc)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, direction, &tex->w, &tex->h);
	if (!tex->img)
		free_list_exit(mlc, "wrong xpm file or xpm path doesn't exist function", 0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (!tex->addr)
		free_list_exit(mlc, "get_data_addr function", 0);
}

t_tex	*get_texture(t_data *data, t_parsing *parsing)
{
	t_tex	*tex;

	tex = l_malloc((sizeof (t_tex) * 4), &parsing->mlc);
	init_tex(data, &tex[0], parsing->no, parsing->mlc);
	init_tex(data, &tex[1], parsing->we, parsing->mlc);
	init_tex(data, &tex[2], parsing->so, parsing->mlc);
	init_tex(data, &tex[3], parsing->ea, parsing->mlc);
	return (tex);
}
