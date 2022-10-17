/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:18 by lide              #+#    #+#             */
/*   Updated: 2022/10/17 14:05:20 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_exit(char *str, int verif)
{
	if (!verif)
		printf("%s", str);
	else
		perror(str);
	exit(EXIT_FAILURE);
}

void	free_list_exit(t_list *adr, char *str)
{
	if (str != NULL)
		printf("%s", str);
	free_list(adr);
	exit(EXIT_FAILURE);
}

void	free_map_lmap(t_list *mlc, t_list *l_map)
{
	free_list(mlc);
	free_list(l_map);
	exit(EXIT_FAILURE);
}
