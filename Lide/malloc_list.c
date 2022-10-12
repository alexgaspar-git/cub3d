
#include "parsing.h"

void	free_list(t_list *adr)
{
	t_list *tmp;

	while(adr->before != NULL)
	{
		adr = adr->before;
	}
	while(adr->next != NULL)
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

void	*l_malloc(size_t size, t_list **adr)
{
	void *ptr;
	t_list *new;

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
			free_list(*adr);
		new->adr = ptr;
		new->before = *adr;
		(*adr)->next = new;
		*adr = (*adr)->next;
		return (ptr);
	}
}
