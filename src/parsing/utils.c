/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:51 by lide              #+#    #+#             */
/*   Updated: 2022/12/02 15:16:18 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	len1(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
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
	s2 = (char *)l_malloc(sizeof(char) * (len + 1), adr);
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

char	*ft_strdup(char *s1, t_list **mlc, int max)
{
	char	*s2;
	int		i;

	s2 = l_malloc(sizeof(char) * (max + 1), mlc);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	while (i < max)
		s2[i++] = ' ';
	s2[i] = 0;
	return (s2);
}

void	skip_w_space(char *str, int *i)
{
	while (str[*i] && ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
}
