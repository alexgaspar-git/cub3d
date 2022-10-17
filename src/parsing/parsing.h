/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:41:51 by lide              #+#    #+#             */
/*   Updated: 2022/10/17 17:11:35 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
// # include "wraloc/wraloc.h"

# define ERROR1 "Cub3d need NO/SO/WE/EA texture and F/C color."
# define ERROR1D " the map content has to be in the last place\n"

typedef struct s_list
{
	void			*adr;
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

typedef struct s_parsing
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f;
	char			*c;
	char			**map;
	struct s_list	*mlc;
}					t_parsing;

t_list	*ft_lstnew(void);
void	*l_malloc(size_t size, t_list **adr);
void	free_list(t_list *adr);

void	init_parsing(t_parsing	**map, t_list *l_map);
void	list_to_char(t_parsing **map, t_list **l_map);

int		len1(char *str);
int		len_s(char *str);
int		ft_cmp(const char *s1, const char *s2, int start, int len);
char	*ft_substr(char *s, int start, t_list **adr);
char	*ft_strdup(char *s1, t_list *mlc);

void	check_map(char **map, t_list *mlc);
void	put_l_map(char *line, t_parsing **map, t_list **l_map);
int		is_map(char *line, t_parsing *map, t_list *l_map);

void	print_exit(char *str, int verif);
void	free_map_lmap(t_list *mlc, t_list *l_map);
void	free_list_exit(t_list *adr, char *str);
t_parsing	*parsing(char **argv, int i);
int		check_name(char *argv);

#endif
