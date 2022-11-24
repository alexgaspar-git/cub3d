/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:23 by lide              #+#    #+#             */
/*   Updated: 2022/11/24 18:55:49 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_name(char *argv)
{
	int	len;

	len = len1(argv);
	if (argv[len - 1] != 'b' || argv[len - 2] != 'u'
		|| argv[len - 3] != 'c' || argv[len - 4] != '.')
	{
		printf("Error\nonly .cub file is accepted\n");
		return (1);
	}
	return (0);
}

void	get_path(char **info, char *line, int i, t_list **adr)
{
	char	*new;
	int		len;

	skip_w_space(line, &i);
	if (*info)
	{
		free_list(*adr);
		free(line);
		printf("Error\nonly one path is accepted for each direction\n");
		exit(EXIT_FAILURE);
	}
	len = len1(&line[i]);
	new = ft_substr(line, i, len, adr);
	if (!new)
	{
		free(line);
		printf("Error\n");
		perror("ft_substr");
		exit (EXIT_FAILURE);
	}
	free(line);
	*info = new;
}

void	check_line2(char *line, t_parsing **map, t_list **l_map, int *check)
{
	if (!is_map(line, *map, *l_map))
	{
		put_l_map(line, map, l_map);
		*check = 1;
	}
}

void	check_line(char *line, t_parsing **map, t_list **l_map)
{
	static int	check;
	int			i;

	if (line[0] == 0 && !check)
	{
		free(line);
		return ;
	}
	i = 0;
	skip_w_space(line, &i);
	if (!ft_cmp(line, "NO ", i, 1) && !check)
		get_path(&(*map)->no, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "SO ", i, 1) && !check)
		get_path(&(*map)->so, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "WE ", i, 1) && !check)
		get_path(&(*map)->we, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "EA ", i, 1) && !check)
		get_path(&(*map)->ea, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "P ", i, 1) && !check)
		get_path(&(*map)->p, line, i + 1, &(*map)->mlc);
	else if (!ft_cmp(line, "F ", i, 0) && !check)
		get_path(&(*map)->f, line, i + 1, &(*map)->mlc);
	else if (!ft_cmp(line, "C ", i, 0) && !check)
		get_path(&(*map)->c, line, i + 1, &(*map)->mlc);
	else
		check_line2(line, map, l_map, &check);
}

t_parsing	*parsing(char **argv, int i)
{
	t_parsing	*map;
	t_list		*l_map;
	char		*line;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_exit("parcing", 1);
	l_map = ft_lstnew();
	if (!l_map)
		print_exit("lstnew", 1);
	init_parsing(&map, l_map);
	while (i)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			free_map_lmap(map->mlc, l_map);
		else if (i == 0)
			break ;
		check_line(line, &map, &l_map);
	}
	list_to_char(&map, &l_map);
	free_list(l_map);
	return (map);
}
