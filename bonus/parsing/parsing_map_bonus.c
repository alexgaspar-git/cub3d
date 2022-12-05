/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:35 by lide              #+#    #+#             */
/*   Updated: 2022/12/05 14:16:31 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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
	{
		free(line);
		return ;
	}
	(*l_map)->adr = line;
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
