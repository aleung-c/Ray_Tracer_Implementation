# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/21 14:52:17 by aleung-c          #+#    #+#              #
#    Updated: 2015/12/03 16:10:03 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

HEADER = includes/rtv1.h \
includes/obj_header.h

SRC = src/rtv1.c \
src/seek_objects.c \
src/display_rt.c \
src/mlx_init.c \
src/init_entry.c \
src/init_scene_definition.c \
src/init_scene_definition2.c \
src/view_plane.c \
src/sphere_check.c \
src/plane_check.c \
src/cylinder_check.c \
src/cone_check.c \
src/add_obj_to_scene.c \
src/cylinder_rotation.c \
src/cone_rotation.c \
src/add_light_to_scene.c \
src/utils_vec.c \
src/utils_vec2.c \
src/utils_angles.c \
src/utils_rotation.c \
src/utils_objects.c \
src/utils_colors.c \
src/vp_vec_touch.c \
src/get_normale.c \
src/shadows.c \
src/shadows_inner.c \
src/shadows_type_filtering.c \
src/shining.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

MLX = -lmlx -framework OpenGL -framework AppKit

CC = gcc -g -Wall -Werror -Wextra -Ofast 

all : Lib $(NAME) 

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./libft/ -lft $(MLX)

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re