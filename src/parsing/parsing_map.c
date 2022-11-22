/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:35 by lide              #+#    #+#             */
/*   Updated: 2022/11/22 17:47:22 by lide             ###   ########.fr       */
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
			|| !(map->ea) || !(map->f) || !(map->c) || !(map->p))
			error_map(map->mlc, l_map, line, ERROR1 ERROR1D);
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W' || line[i] == 'P')
			i++;
		else
		{
			printf("Error\n");
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
			printf("Error\n");
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
	(*l_map)->adr = line;// le probleme est la !
	new = ft_lstnew();
	if (!new)
	{
		printf("Error\n");
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

void	check_map2(t_parsing *map, int *player, int *x, int y)
{
	if (map->map[y][*x] != '0'
		&& map->map[y][*x] != ' ' && map->map[y][*x] != '1'
		&& map->map[y][*x] != 'P')
		if (++(*player) > 1)
			free_list_exit(map->mlc, "only one player is accepted", 0);
	if (map->map[y][*x] != ' ' && map->map[y][*x] != '1')
		if (y == 0 || check_map_wall(map->map, y, *x))
			free_list_exit(map->mlc, "map is not closed", 0);
	(*x)++;
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
			check_map2(map, &player, &x, y);
		y++;
	}
	if (player == 0)
		free_list_exit(map->mlc, "one player is required", 0);
	check_texture_xpm(map);
	find_map_limits(map);
}
