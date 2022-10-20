/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:35 by lide              #+#    #+#             */
/*   Updated: 2022/10/20 18:47:20 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_map(char *line, t_parsing *map, t_list *l_map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(map->no) || !(map->so) || !(map->we)
			|| !(map->ea) || !(map->f) || !(map->c))
		{
			printf(ERROR1 ERROR1D);
			free(line);
			free_map_lmap(map->mlc, l_map);
		}
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			i++;
		else
		{
			printf("there is a wrong charactere in the map ->|%c|\n", line[i]);
			free(line);
			free_map_lmap(map->mlc, l_map);
		}
	}
	return (0);
}

int	check_last(char *line, t_parsing **map, t_list **l_map)
{
	static int	empty;

	if (line[0] == 0 && !empty)
	{
		empty = 1;
		return (1);
	}
	if (empty)
	{
		if (line[0] != 0)
		{
			printf("map can't be separeted and must be the last argument\n");
			free(line);
			free_map_lmap((*map)->mlc, *l_map);
		}
		else
			return (1);
	}
	return (0);
}

void	put_l_map(char *line, t_parsing **map, t_list **l_map)
{
	t_list		*new;

	if (check_last(line, map, l_map))
		return ;
	(*l_map)->adr = line;
	new = ft_lstnew();
	if (!new)
	{
		perror("lstnew");
		free(line);
		free_map_lmap((*map)->mlc, *l_map);
	}
	(*l_map)->next = new;
	new->before = *l_map;
	*l_map = (*l_map)->next;
}

int	check_map_wall(char **map, const int y, const int x)
{
	int	y2;
	int	x2;

	y2 = y;
	while (map[y2] && map[y2][x] && map[y2][x] != '1' && map[y2][x] != ' ')
		y2--;
	if (!map[y2] || !map[y2][x] || map[y2][x] == ' ')
		return (1);
	y2 = y;
	while (map[y2] && map[y2][x] && map[y2][x] != '1' && map[y2][x] != ' ')
		y2++;
	if (!map[y2] || !map[y2][x] || map[y2][x] == ' ')
		return (1);
	x2 = x;
	while (map[y][x2] && map[y][x2] != '1' && map[y][x2] != ' ')
		x2--;
	if (!map[y][x2] || map[y][x2] == ' ')
		return (1);
	x2 = x;
	while (map[y][x2] && map[y][x2] != '1' && map[y][x2] != ' ')
		x2++;
	if (!map[y][x2] || map[y][x2] == ' ')
		return (1);
	return (0);
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

void	check_texture(t_parsing *map)
{
	check_xpm(map->no, map->mlc);
	check_xpm(map->so, map->mlc);
	check_xpm(map->we, map->mlc);
	check_xpm(map->ea, map->mlc);
}

void	find_map_limits(t_parsing *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x++])
			if (x > map->x_max)
				map->x_max = x;
		y++;
	}
	map->y_max = y;
}

void	check_map(t_parsing *map)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] != '0'
			&& map->map[y][x] != ' ' && map->map[y][x] != '1')
				if (++player > 1)
					free_list_exit(map->mlc, "only one player is accepted\n");
			if (map->map[y][x] != ' ' && map->map[y][x] != '1')
				if (y == 0 || check_map_wall(map->map, y, x))
					free_list_exit(map->mlc, "map is not closed\n");
			x++;
		}
		y++;
	}
	check_texture(map);
	find_map_limits(map);
}
