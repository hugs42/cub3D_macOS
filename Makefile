#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 17:54:36 by hugsbord          #+#    #+#              #
#    Updated: 2021/04/05 17:44:48 by hugsbord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = ./srcs/cub3d.c \
	./srcs/get_next_line.c \
	./srcs/init.c \
	./srcs/init_2.c \
	./srcs/parser.c \
	./srcs/parser_utils.c \
	./srcs/get_map.c \
	./srcs/check_arg.c \
	./srcs/check_config.c \
	./srcs/check_neighborhood.c \
	./srcs/check_map.c \
	./srcs/check_map_2.c \
	./srcs/cub3d_utils.c \
	./srcs/key_events.c \
	./srcs/textures.c \
	./srcs/raycasting.c \
	./srcs/raycasting_2.c \
	./srcs/move.c \
	./srcs/rot.c \
	./srcs/color_parser.c \
	./srcs/player.c \
	./srcs/render_raycasting.c \
	./srcs/config_parser.c \
	./srcs/sprites.c \
	./srcs/sprites_2.c \
	./srcs/bmp_save.c \
	./srcs/error.c \
	./srcs/exit.c

INC = -I./inc

FLAGS = -Wall -Wextra -Werror #-fsanitize=leak

LIBS=$(LIBS_MAC)
MLX_D = ./minilibx-linux

LIBS_MAC =-L ./libft -lft -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBS_LINUX =-L ./libft -L $(MLX_D) -lft -lmlx -lm -lbsd -lX11 -lXext

OBJ=$(SRCS:.c=.o)

%.o: %.c
	clang $(INC) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	clang $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBS)

clean: $(OBJ)
	@make $@ -C libft
	rm -f $(OBJ)

fclean: clean
	@make $@ -C libft
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all, clean, fclean, re
