/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:32:23 by lide              #+#    #+#             */
/*   Updated: 2022/10/10 18:52:08 by lide             ###   ########.fr       */
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

void	init_parsing(t_parcing *map)
{
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
	map->F = NULL;
	map->C = NULL;
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

char	*ft_substr(char *s, unsigned int start, int len)
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
	s2 = (char *)malloc(sizeof(char) * (len + 1));
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

void	get_path(char **info, char *line, int i)
{
	int len;
	char *new;

	while(line[i] == ' ')
		i++;
	len = path_len(&line[i]);
	if (len == -1 || *info)
	{
		printf("only one path is accepted\n");
		exit(EXIT_FAILURE);
	}
	new = ft_substr(line, i, len);
	if (!new)
	{
		perror("ft_substr");
		exit (EXIT_FAILURE);
	}
	free(line);
	*info = new;
}

void	check_line(char *line, t_parcing *map)
{
	int i;

	if (line[0] == 0)
		return ;
	i = 0;
	while(line[i] == ' ')
		i++;
	if (!ft_cmp(line, "NO ", i, 2))
		get_path(&map->NO, line, i + 2);
	else if (!ft_cmp(line, "SO ", i, 2))
		get_path(&map->SO, line, i + 2);
	else if (!ft_cmp(line, "WE ", i, 2))
		get_path(&map->WE, line, i + 2);
	else if (!ft_cmp(line, "EA ", i, 2))
		get_path(&map->EA, line, i + 2);
	else if (!ft_cmp(line, "F ", i, 1))
		get_path(&map->F, line, i + 2);
	else if (!ft_cmp(line, "C ", i, 1))
		get_path(&map->C, line, i + 2);
}

int main(int argc, char **argv)
{
	t_parcing map;
	char *line;
	int verif;
	int	fd;
	int	i;

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
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("parcing");
		exit(EXIT_FAILURE);
	}
	i = 1;
	init_parsing(&map);
	while (i)
	{
		i = get_next_line(fd, &line);
		if (i == -1)
			exit(EXIT_FAILURE);
		else if (i == 0)
			break;
		check_line(line, &map);
	}
	printf("|NO = %s|\n|SO = %s|\n|WE = %s|\n|EA = %s|\n|F = %s|\n|C = %s|\n", map.NO, map.SO, map.WE, map.EA, map.F, map.C);
}
