# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 17:54:36 by hugsbord          #+#    #+#              #
#    Updated: 2021/03/27 11:49:22 by hugsbord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = ./srcs/main.c \
	./srcs/get_next_line.c \
	./srcs/init.c \
	./srcs/init_2.c \
	./srcs/parser.c \
	./srcs/parser_utils.c \
	./srcs/map_parser.c \
	./srcs/map_parser_2.c \
	./srcs/check.c \
	./srcs/cub3d_utils.c \
	./srcs/key_events.c \
	./srcs/textures.c \
	./srcs/init_raycasting.c \
	./srcs/color_parser.c \
	./srcs/player.c \
	./srcs/render.c \
	./srcs/config_parser.c \
	./srcs/error.c

INC = -I./inc

FLAGS = -Wall -Wextra -Werror # -fsanitize=address

LIBS=$(LIBS_MAC)

LIBS_MAC =-L ./libft -lft -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBS_LINUX =-L ./libft -lft -I /usr/local/include -L /usr/local/lib -lmlx -L/usr/include -lm -lbsd -lX11 -lX$

OBJ=$(SRCS:.c=.o)

%.o: %.c
	clang $(INC) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	clang $(INC) -o $(NAME) $(OBJ) $(LIBS)

clean: $(OBJ)
	make $@ -C libft
	rm -f $(OBJ)

fclean: clean
	make $@ -C libft
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all, clean, fclean, re
