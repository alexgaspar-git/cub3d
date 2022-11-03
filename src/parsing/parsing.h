/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:41:51 by lide              #+#    #+#             */
/*   Updated: 2022/11/03 14:45:39 by lide             ###   ########.fr       */
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
# define ERROR1D " the map content has to be in the last place"

typedef struct s_list
{
	void			*adr;
	struct s_list	*next;
	struct s_list	*before;
}					t_list;

typedef struct s_parsing
{
	int				x_max;
	int				y_max;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*p;
	char			*f;
	char			*c;
	char			**map;
	struct s_list	*mlc;
}					t_parsing;

t_list		*ft_lstnew(void);
void		*l_malloc(size_t size, t_list **adr);
void		free_list(t_list *adr);

void		init_parsing(t_parsing	**map, t_list *l_map);
void		list_to_char(t_parsing **map, t_list **l_map);

int			len1(char *str);
int			ft_cmp(const char *s1, const char *s2, int start, int len);
char		*ft_substr(char *s, int start, int len, t_list **adr);
char		*ft_strdup(char *s1, t_list *mlc);
void		skip_w_space(char *str, int *i);

void		check_map(t_parsing *map);
void		put_l_map(char *line, t_parsing **map, t_list **l_map);
int			is_map(char *line, t_parsing *map, t_list *l_map);

void		print_exit(char *str, int verif);
void		free_map_lmap(t_list *mlc, t_list *l_map);
void		error_map(t_list *mlc, t_list *l_map, char *line, char *str);
void		free_list_exit(t_list *adr, char *str, int verif);
int			check_name(char *argv);
t_parsing	*parsing(char **argv, int i);

int			check_colours(char *colour);
int			print_error(char *str);

void		check_texture(t_parsing *map);
void		check_texture_xpm(t_parsing *map);
unsigned int	rgb_to_hex(char	*color);

#endif
