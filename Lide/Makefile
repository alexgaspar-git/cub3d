# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lide <lide@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 16:13:19 by lide              #+#    #+#              #
#    Updated: 2022/10/14 12:13:34 by lide             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	parsing.c\
				get_next_line/get_next_line.c\
				get_next_line/get_next_line_utils.c\
				malloc_list.c

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
