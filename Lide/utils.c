/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:05:51 by lide              #+#    #+#             */
/*   Updated: 2022/10/17 14:05:52 by lide             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	len1(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	len_s(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
		if (str[i++] != ' ')
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

char	*ft_substr(char *s, int start, t_list **adr)
{
	char	*s2;
	int		len2;
	int		i;

	if (!s)
		return (NULL);
	len2 = len_s(&s[start]);
	s2 = l_malloc(sizeof(char) * (len2 + 1), adr);
	if (!s2)
		return (NULL);
	i = 0;
	while (s[start] && i < len2)
	{
		if (s[start] == ' ')
			start++;
		else
			s2[i++] = s[start++];
	}
	s2[i] = 0;
	return (s2);
}

char	*ft_strdup(char *s1, t_list *mlc)
{
	char	*s2;
	int		i;

	s2 = l_malloc(sizeof(char) * (len1(s1) + 1), &mlc);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}
