/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:24 by lide              #+#    #+#             */
/*   Updated: 2022/12/05 14:16:26 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	init_parsing(t_parsing	**map, t_list *l_map)
{
	t_list	*mlc;

	mlc = ft_lstnew();
	if (!mlc)
		free_list_exit(l_map, "lstnew", 1);
	*map = l_malloc(sizeof(t_parsing), &mlc);
	if (!*map)
		free_list_exit(l_map, "init_parsing", 1);
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	(*map)->p = NULL;
	(*map)->f = NULL;
	(*map)->c = NULL;
	(*map)->x_max = 0;
	(*map)->y_max = 0;
	(*map)->mlc = mlc;
}

int	find_x_max(t_list *map)
{
	int	len;
	int	len2;

	len = 0;
	while (map->adr != NULL)
	{
		len2 = len1(map->adr);
		if (len2 > len)
			len = len2;
		map = map->next;
	}
	return (len);
}

int	list_len(t_list **l_map)
{
	int	len;

	len = 0;
	while ((*l_map)->before != NULL)
	{
		*l_map = (*l_map)->before;
		len++;
	}
	return (len);
}

void	list_to_char(t_parsing **map, t_list **l_map)
{
	char	**save;
	t_list	*tmp;
	int		len;
	int		max;
	int		i;

	len = list_len(l_map);
	max = find_x_max(*l_map);
	save = l_malloc(sizeof(char *) * (len + 1), &(*map)->mlc);
	if (!save)
		free_list_exit(*l_map, "list_to_char", 1);
	i = 0;
	tmp = *l_map;
	while (tmp->adr != NULL)
	{
		save[i] = ft_strdup(tmp->adr, &(*map)->mlc, max);
		if (!save[i++])
			free_list_exit(*l_map, "list_to_char : strdup", 1);
		tmp = tmp->next;
	}
	save[i] = NULL;
	(*map)->map = save;
}
