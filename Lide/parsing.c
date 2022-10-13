/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:23 by lide              #+#    #+#             */
/*   Updated: 2022/10/13 18:47:49 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	len1(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	path_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	i = len;
	while (str[i])
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (len);
}

int	check_name(char *argv)
{
	int	len;

	len = len1(argv);
	if (argv[len - 1] != 'b' || argv[len - 2] != 'u'
		|| argv[len - 3] != 'c' || argv[len - 4] != '.')
	{
		write(2, "Error : only .cub file is accepted\n", 35);
		return (1);
	}
	return (0);
}

void	init_parsing(t_parsing	**map, t_list *l_map)
{
	t_list	*mlc;

	mlc = ft_lstnew();
	if (!mlc)
	{
		perror("lstnew");
		free_list(l_map);
		exit(EXIT_FAILURE);
	}
	*map = l_malloc(sizeof(t_parsing), &mlc);
	if (!*map)
	{
		perror("init_parsing");
		free_list(l_map);
		exit(EXIT_FAILURE);
	}
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	(*map)->f = NULL;
	(*map)->c = NULL;
	(*map)->mlc = mlc;
}

int	ft_cmp(const char *s1, const char *s2, int start, int len)
{
	int	i;

	i = 0;
	while (s1[start] && s2[i] && s1[start] == s2[i] && i < len)
	{
		i++;
		start++;
	}
	return ((unsigned char)s1[start] - (unsigned char)s2[i]);
}

char	*ft_substr(char *s, int start, int len, t_list **adr)
{
	char	*s2;
	int		len2;
	int		i;

	if (!s)
		return (NULL);
	len2 = len1(s);
	if (start >= len2)
		start = len2;
	if (len2 - start < len)
		len = len2 - start;
	s2 = l_malloc(sizeof(char) * (len + 1), adr);
	if (!s2)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		s2[i] = s[start];
		start++;
		i++;
	}
	s2[i] = 0;
	return (s2);
}

void	get_path(char **info, char *line, int i, t_list **adr)
{
	int		len;
	char	*new;

	while (line[i] == ' ')
		i++;
	len = path_len(&line[i]);
	if (len == -1 || *info)
	{
		free_list(*adr);
		free(line);
		printf("only one path is accepted for each direction\n");
		exit(EXIT_FAILURE);
	}
	new = ft_substr(line, i, len, adr);
	if (!new)
	{
		free(line);
		perror("ft_substr");
		exit (EXIT_FAILURE);
	}
	free(line);
	*info = new;
}

void	free_map_lmap(t_list *mlc, t_list *l_map)
{
	free_list(mlc);
	free_list(l_map);
	exit(EXIT_FAILURE);
}

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

void	check_line(char *line, t_parsing **map, t_list **l_map)
{
	static int	check;
	int			i;

	if (line[0] == 0 && !check)
		return ;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (!ft_cmp(line, "NO ", i, 1) && !check)
		get_path(&(*map)->no, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "SO ", i, 1) && !check)
		get_path(&(*map)->so, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "WE ", i, 1) && !check)
		get_path(&(*map)->we, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "EA ", i, 1) && !check)
		get_path(&(*map)->ea, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "F ", i, 0) && !check)
		get_path(&(*map)->f, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "C ", i, 0) && !check)
		get_path(&(*map)->c, line, i + 2, &(*map)->mlc);
	else if (!is_map(line, *map, *l_map))
	{
		put_l_map(line, map, l_map);
		check = 1;
	}
}

char	*ft_strdup(char *s1, t_list *mlc)
{
	char	*s2;
	int		i;

	s2 = l_malloc(sizeof(char) * (len1(s1) + 1), &mlc);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

void	free_list_exit(t_list *adr)
{
	free_list(adr);
	exit(EXIT_FAILURE);
}

void	list_to_char(t_parsing **map, t_list **l_map)
{
	char	**save;
	t_list	*tmp;
	int		len;
	int		i;

	len = 1;//verif
	while ((*l_map)->before != NULL)
	{
		*l_map = (*l_map)->before;
		len++;
	}
	save = l_malloc(sizeof(char *) * (len + 1), &(*map)->mlc);
	if (!save)
		free_list_exit(*l_map);
	i = 0;
	tmp = *l_map;
	while (tmp->adr != NULL)
	{
		save[i] = ft_strdup(tmp->adr, (*map)->mlc);
		if (!save[i++])
			free_list_exit(*l_map);
		tmp = tmp->next;
	}
	save[i] = NULL;
	(*map)->map = save;
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

void	check_map(char **map, t_list *mlc)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != ' ' && map[y][x] != '1')
			{
				if (++player > 1)
				{
					printf("only one player is accepted\n");
					free_list(mlc);
					exit(EXIT_FAILURE);
				}
			}
			if (map[y][x] != ' ' && map[y][x] != '1')
			{
				if (check_map_wall(map, y, x))
				{
					printf("map is not closed\n");
					free_list(mlc);
					exit(EXIT_FAILURE);
				}
			}
			x++;
		}
		y++;
	}
}

t_parsing	*parsing(char **argv)
{
	t_parsing	*map;
	t_list		*l_map;
	char		*line;
	int			fd;
	int			i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("parcing");
		exit(EXIT_FAILURE);
	}
	i = 1;
	l_map = ft_lstnew();
	if (!l_map)
	{
		perror("lstnew");
		exit(EXIT_FAILURE);
	}
	init_parsing(&map, l_map);
	while (i)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
		{
			free_list(map->mlc);
			free_list(l_map);
			exit(EXIT_FAILURE);
		}
		else if (i == 0)
			break ;
		check_line(line, &map, &l_map);
	}
	list_to_char(&map, &l_map);
	free_list(l_map);
	check_map(map->map, map->mlc);
	return (map);
}

int	main(int argc, char **argv)
{
	t_parsing	*map;

	if (argc < 2)
	{
		printf("cub3d need a map\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		printf("too much information\n");
		exit(EXIT_FAILURE);
	}
	if (check_name(argv[1]))
		exit(EXIT_FAILURE);
	map = parsing(argv);
	printf("|no = %s|\n|so = %s|\n|we = %s|\n|ea = %s|\n|f = %s|\n|c = %s|\n", map->no, map->so, map->we, map->ea, map->f, map->c);
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	free_list(map->mlc);
}
