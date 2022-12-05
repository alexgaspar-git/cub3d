/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colour_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:15:52 by lide              #+#    #+#             */
/*   Updated: 2022/12/05 17:06:39 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	print_error(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	return (1);
}

int	atoi255(const char *str, int i)
{
	long	j;

	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j *= 10;
		j += str[i] - '0';
		i++;
	}
	return (j);
}

int	check255(char *colour, int *i, int len)
{
	int	num;

	if (!colour[*i])
		return (print_error("not enough information for the C or F"));
	while (colour[*i]
		&& ((colour[*i] >= 9 && colour[*i] <= 13) || colour[*i] == ' '))
		(*i)++;
	while (colour[*i] && colour[*i] >= '0' && colour[*i] <= '9')
	{
		(*i)++;
		len++;
	}
	if (len == 0)
	{
		if (colour[*i] != ',')
			return (print_error("only digits and comma are accepted"));
		else
			return (print_error("need a digit before the comma"));
	}
	else if (len > 3)
		return (print_error("255 is the max value"));
	num = atoi255(colour, *i - len);
	if (num > 255)
		return (print_error("255 is the max value"));
	return (0);
}

int	check_comma(char *colour, int *i)
{
	skip_w_space(colour, i);
	if (colour[*i] && colour[*i] >= '0' && colour[*i] <= '9')
		return (print_error("need a comma to separate digits"));
	else if (colour[*i] && colour[*i] != ',')
		return (print_error("only digits and comma are accepted"));
	else if (colour[*i])
		(*i)++;
	if (!colour[*i])
		return (print_error("not enough information for the C or F"));
	return (0);
}

int	check_colours(char *colour)
{
	int	i;

	i = 0;
	if (check255(colour, &i, 0))
		return (1);
	if (check_comma(colour, &i))
		return (1);
	if (check255(colour, &i, 0))
		return (1);
	if (check_comma(colour, &i))
		return (1);
	if (check255(colour, &i, 0))
		return (1);
	while (colour[i])
	{
		if (colour[i]
			&& !((colour[i] >= 9 && colour[i] <= 13) || colour[i] == ' '))
		{
			print_error("too much information for the C or F");
			exit(EXIT_FAILURE);// peut etre free;
		}
		i++;
	}
	return (0);
}
