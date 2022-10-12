/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:23 by lide              #+#    #+#             */
/*   Updated: 2022/10/12 17:59:02 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	len1(char *str)
{
	int len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

int path_len(char *str)
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
	t_list *mlc;

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
	(*map)->NO = NULL;
	(*map)->SO = NULL;
	(*map)->WE = NULL;
	(*map)->EA = NULL;
	(*map)->F = NULL;
	(*map)->C = NULL;
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
	int len;
	char *new;

	while(line[i] == ' ')
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

int	is_map(char *line, t_parsing *map, t_list *l_map)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == ' ' || line[i] == '0' || line[i] == '1'
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E'|| line[i] == 'W')
			i++;
		else if (!(map->NO) || !(map->SO) || !(map->WE)
		|| !(map->EA) || !(map->F) || !(map->C))
		{
			printf("Cub3d need NO/SO/WE/EA texture and F/C color. the map content has to be in the last place\n");
			free_list(map->mlc);
			free_list(l_map);
			free(line);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("there is a wrong charactere in the map\n");
			free_list(map->mlc);
			free_list(l_map);
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	put_l_map(char *line, t_parsing **map, t_list **l_map)
{
	t_list	*new;
	static int empty;

	if (line[0] == 0 && !empty)
	{
		empty = 1;
		return ;
	}
	if (empty)
	{
		if (line[0] != 0)
		{
			printf("map can't be separeted and must be the last argument\n");
			free_list((*map)->mlc);
			free_list(*l_map);
			free(line);
			exit(EXIT_FAILURE);
		}
		else
			return ;
	}
	printf("%s\n", line);
	(*l_map)->adr = line;
	new = ft_lstnew();
	if (!new)
	{
		free_list((*map)->mlc);
		free_list(*l_map);
		free(line);
		perror("lstnew");
		exit(EXIT_FAILURE);
	}
	(*l_map)->next = new;
	*l_map = (*l_map)->next;
}

void	check_line(char *line, t_parsing **map, t_list **l_map)
{
	static int	check;
	int			i;

	if (line[0] == 0 && !check)
		return ;
	i = 0;
	while(line[i] == ' ')
		i++;
	if (!ft_cmp(line, "NO ", i, 2) && !check)
		get_path(&(*map)->NO, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "SO ", i, 2) && !check)
		get_path(&(*map)->SO, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "WE ", i, 2) && !check)
		get_path(&(*map)->WE, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "EA ", i, 2) && !check)
		get_path(&(*map)->EA, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "F ", i, 1) && !check)
		get_path(&(*map)->F, line, i + 2, &(*map)->mlc);
	else if (!ft_cmp(line, "C ", i, 1) && !check)
		get_path(&(*map)->C, line, i + 2, &(*map)->mlc);
	else if (!is_map(line, *map, *l_map))
	{
		put_l_map(line, map, l_map);
		check = 1;
	}
}

t_parsing	*parsing(char **argv)
{
	t_parsing	*map;
	char		**c_map;
	t_list		*l_map;
	char *line;
	int	fd;
	int	i;

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
			break;
		check_line(line, &map, &l_map);
	}
	//transformer map en char ** puis check si map good
	free_list(l_map);
	return (map);
}

int main(int argc, char **argv)
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
	printf("|NO = %s|\n|SO = %s|\n|WE = %s|\n|EA = %s|\n|F = %s|\n|C = %s|\n", map->NO, map->SO, map->WE, map->EA, map->F, map->C);
	free_list(map->mlc);
}
