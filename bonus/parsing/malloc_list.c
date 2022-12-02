/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:34 by lide              #+#    #+#             */
/*   Updated: 2022/12/02 15:16:18 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	free_list(t_list *adr)
{
	t_list	*tmp;

	while (adr->before != NULL)
		adr = adr->before;
	while (adr->next != NULL)
	{
		tmp = adr;
		adr = adr->next;
		free(tmp->adr);
		free(tmp);
	}
	free(adr->adr);
	free(adr);
}

t_list	*ft_lstnew(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->before = NULL;
	list->adr = NULL;
	return (list);
}

void	free_l_malloc_error(void *ptr, t_list **adr)
{
	(void)ptr;
	free_list(*adr);
	free(ptr);
	exit(EXIT_FAILURE);
}

void	*l_malloc(size_t size, t_list **adr)
{
	void	*ptr;
	t_list	*new;
	static int i;

	i++;
	ptr = malloc(size);
	if (!ptr)
	{
		free_list(*adr);
		return (NULL);
	}
	if ((*adr)->adr == NULL)
	{
		(*adr)->adr = ptr;
		return (ptr);
	}
	else
	{
		new = ft_lstnew();
		if (!new)
			free_l_malloc_error(ptr, adr);
		new->adr = ptr;
		new->before = *adr;
		(*adr)->next = new;
		*adr = (*adr)->next;
		return (ptr);
	}
}
