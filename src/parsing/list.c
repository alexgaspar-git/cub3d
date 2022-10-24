/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:24 by lide              #+#    #+#             */
/*   Updated: 2022/10/24 16:55:12 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	(*map)->f = NULL;
	(*map)->c = NULL;
	(*map)->x_max = 0;
	(*map)->y_max = 0;
	(*map)->mlc = mlc;
}

void	list_to_char(t_parsing **map, t_list **l_map)
{
	char	**save;
	t_list	*tmp;
	int		len;
	int		i;

	len = 0;
	while ((*l_map)->before != NULL)
	{
		*l_map = (*l_map)->before;
		len++;
	}
	save = l_malloc(sizeof(char *) * (len + 1), &(*map)->mlc);
	if (!save)
		free_list_exit(*l_map, "list_to_char", 1);
	i = 0;
	tmp = *l_map;
	while (tmp->adr != NULL)
	{
		save[i] = ft_strdup(tmp->adr, (*map)->mlc);
		if (!save[i++])
			free_list_exit(*l_map, "list_to_char : strdup", 1);
		tmp = tmp->next;
	}
	save[i] = NULL;
	(*map)->map = save;
}
