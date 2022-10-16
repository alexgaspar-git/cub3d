# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 16:13:19 by lide              #+#    #+#              #
#    Updated: 2022/10/16 14:47:41 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	free.c\
				list.c\
				utils.c\
				parsing.c\
				parsing_map.c\
				malloc_list.c\
				get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}

NAME		= cub3d

CC			= gcc

MAKE		= make

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra -Iinclude

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
