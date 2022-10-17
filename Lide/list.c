/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:24 by lide              #+#    #+#             */
/*   Updated: 2022/10/17 14:18:55 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		free_list_exit(*l_map, NULL);
	i = 0;
	tmp = *l_map;
	while (tmp->adr != NULL)
	{
		save[i] = ft_strdup(tmp->adr, (*map)->mlc);
		if (!save[i++])
			free_list_exit(*l_map, NULL);
		tmp = tmp->next;
	}
	save[i] = NULL;
	(*map)->map = save;
}