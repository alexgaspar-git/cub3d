/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:23 by lide              #+#    #+#             */
/*   Updated: 2022/10/21 18:22:39 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	path_len(char *str)
// {
// 	int	len;
// 	int	i;

// 	len = 0;
// 	while (str[len] && str[len] != ' ')
// 		len++;
// 	i = len;
// 	while (str[i])
// 	{
// 		if (str[i] != ' ')
// 			return (-1);
// 		i++;
// 	}
// 	return (len);
// }

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

void	get_path(char **info, char *line, int i, t_list **adr)
{
	char	*new;
	int		len;

	while (line[i] == ' ')
		i++;
	if (*info)
	{
		free_list(*adr);
		free(line);
		printf("only one path is accepted for each direction\n");
		exit(EXIT_FAILURE);
	}
	len = len1(&line[i]);
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
	check_map(map);
	// check_texture(map);
	// printf("|no = %s|\n|so = %s|\n|we = %s|\n|ea = %s|\n|f = %s|\n|c = %s|\n", map->no, map->so, map->we, map->ea, map->f, map->c);
	return (map);
}

// int	main(int argc, char **argv)
// {
// 	t_parsing	*map;

// 	if (argc < 2)
// 	{
// 		printf("cub3d need a map\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (argc > 2)
// 	{
// 		printf("too much information\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (check_name(argv[1]))
// 		exit(EXIT_FAILURE);
// 	map = parsing(argv, 1);
// 	printf("|no = %s|\n|so = %s|\n|we = %s|\n|ea = %s|\n|f = %s|\n|c = %s|\n", map->no, map->so, map->we, map->ea, map->f, map->c);
// 	for (int i = 0; map->map[i]; i++)
// 		printf("%s\n", map->map[i]);
// 	free_list(map->mlc);
// }
