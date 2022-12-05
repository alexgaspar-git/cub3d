SRCS		= 	main.c \
				bresenham.c \
				init.c \
				init_utils.c \
				utils.c \
				frame.c \
				is_wall.c \
				get_player_dir.c \
				add_pixel.c \
				is_wall_utils.c \
				get_ray.c \
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
				parsing/parsing_map2.c\
				parsing/malloc_list.c\
				parsing/check_colour.c\
				parsing/check_texture.c\
				parsing/get_next_line/get_next_line.c\
				parsing/get_next_line/get_next_line_utils.c

SRCS_BONUS	= 	main_bonus.c \
				bresenham_bonus.c \
				init_bonus.c \
				init_utils_bonus.c \
				utils_bonus.c \
				frame_bonus.c \
				minimap_bonus.c \
				minimap_utils_bonus.c \
				is_wall_bonus.c \
				door_bonus.c \
				get_player_dir_bonus.c\
				is_wall_utils_bonus.c \
				get_ray_bonus.c \
				raycasting_bonus.c \
				open_texture_bonus.c \
				move_player_bonus.c \
				hook_functions_bonus.c \
				dr_texture_bonus.c \
				add_pixel_bonus.c \
				parsing/free_bonus.c\
				parsing/list_bonus.c\
				parsing/utils_bonus.c\
				parsing/parsing_bonus.c\
				parsing/split_bonus.c\
				parsing/get_rgb_bonus.c\
				parsing/parsing_map_bonus.c\
				parsing/parsing_map2_bonus.c\
				parsing/malloc_list_bonus.c\
				parsing/check_colour_bonus.c\
				parsing/check_texture_bonus.c\
				parsing/get_next_line/get_next_line_bonus.c\
				parsing/get_next_line/get_next_line_utils_bonus.c

SRCS		:= $(addprefix mandatory/,$(SRCS))

SRCS_BONUS	:= $(addprefix bonus/,$(SRCS_BONUS))

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= cub3D

NAME_BONUS 	= cub3D_bonus

CC			= gcc

MAKE		= make

RM			= rm -rf

CFLAGS		= -Wall -Werror -Wextra -Iinclude

$(NAME):	$(OBJS)
			$(CC) ${CFLAGS} -o $(NAME) -lmlx -framework OpenGL -framework AppKit $(OBJS)

$(NAME_BONUS):	$(OBJS_BONUS)
				$(CC) ${CFLAGS} -o $(NAME_BONUS) -lmlx -framework OpenGL -framework AppKit $(OBJS_BONUS)

all:		$(NAME)

bonus:		$(NAME_BONUS)

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} $(NAME) ${NAME_BONUS}

re:			fclean all

.PHONY:		all clean fclean re bonus
