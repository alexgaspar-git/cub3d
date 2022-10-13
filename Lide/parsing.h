/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lide <lide@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:41:51 by lide              #+#    #+#             */
/*   Updated: 2022/10/13 18:47:56 by lide             ###   ########.fr       */
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

# define ERROR1 "Cub3d need no/so/we/ea texture and F/C color."
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

#endif
