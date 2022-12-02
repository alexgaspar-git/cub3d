/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:45:54 by lide              #+#    #+#             */
/*   Updated: 2022/12/02 15:16:18 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	check_space_t(char *texture)
{
	int	i;

	i = 0;
	skip_w_space(texture, &i);
	while (texture[i]
		&& !((texture[i] >= 9 && texture[i] <= 13) || texture[i] == ' '))
		i++;
	skip_w_space(texture, &i);
	if (texture[i])
		return (print_error("wrong texture path"));
	return (0);
}

void	check_texture(t_parsing *map)
{
	if (check_space_t(map->no))
		free_list_exit(map->mlc, NULL, 0);
	if (check_space_t(map->so))
		free_list_exit(map->mlc, NULL, 0);
	if (check_space_t(map->ea))
		free_list_exit(map->mlc, NULL, 0);
	if (check_space_t(map->we))
		free_list_exit(map->mlc, NULL, 0);
	if (check_space_t(map->p))
		free_list_exit(map->mlc, NULL, 0);
	if (check_colours(map->c))
		free_list_exit(map->mlc, NULL, 0);
	if (check_colours(map->f))
		free_list_exit(map->mlc, NULL, 0);
}

void	check_xpm(char *line, t_list *adr)
{
	int	len;

	len = len1(line);
	if (line[len - 1] != 'm' || line[len - 2] != 'p'
		|| line[len - 3] != 'x' || line[len - 4] != '.')
	{
		free_list(adr);
		printf("only .xpm is accepted for texture\n");
		exit(EXIT_FAILURE);
	}
}

void	check_texture_xpm(t_parsing *map)
{
	check_xpm(map->no, map->mlc);
	check_xpm(map->so, map->mlc);
	check_xpm(map->we, map->mlc);
	check_xpm(map->ea, map->mlc);
	check_xpm(map->p, map->mlc);
}
