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

HEADER = RTv1.h

SRC = RTv1.c sphere_check.c add_obj_to_scene.c utils_vec.c utils_angles.c \
utils_objects.c vp_vec_touch.c

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