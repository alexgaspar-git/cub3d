SRCS		= 	main.c \
				bresenham.c \
				init.c \
				init_utils.c \
				utils.c \
				frame.c \
				minimap.c \
				is_wall.c \
				door.c \
				is_wall_utils.c \
				raycasting.c \
				open_texture.c \
				move_player.c \
				hook_functions.c \
				dr_texture.c\
				parsing/free.c\
				parsing/list.c\
				parsing/utils.c\
				parsing/parsing.c\
				parsing/split.c\
				parsing/get_rgb.c\
				parsing/parsing_map.c\
				parsing/malloc_list.c\
				parsing/check_colour.c\
				parsing/check_texture.c\
				parsing/get_next_line/get_next_line.c\
				parsing/get_next_line/get_next_line_utils.c

SRCS		:= $(addprefix src/,$(SRCS))

OBJS		= ${SRCS:.c=.o}

NAME		= cub3d

CC			= gcc

MAKE		= make

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra -Iinclude

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) -lmlx -framework OpenGL -framework AppKit $(OBJS)

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

noice:		all clean

.PHONY:		all clean fclean re bonus
