/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:18 by lide              #+#    #+#             */
/*   Updated: 2022/11/23 18:37:11 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_exit(char *str, int verif)
{
	printf("Error\n");
	if (!verif)
		printf("%s\n", str);
	else
		perror(str);
	exit(EXIT_FAILURE);
}

void	free_list_exit(t_list *adr, char *str, int verif)
{
	if (str)
		printf("Error\n");
	if (!verif && str)
		printf("%s\n", str);
	else if (str)
		perror(str);
	free_list(adr);
	exit(EXIT_FAILURE);
}

void	error_map(t_list *mlc, t_list *l_map, char *line, char *str)
{
	printf("Error\n%s\n", str);
	free(line);
	free_map_lmap(mlc, l_map);
}

void	free_map_lmap(t_list *mlc, t_list *l_map)
{
	free_list(mlc);
	free_list(l_map);
	exit(EXIT_FAILURE);
}
