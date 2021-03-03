# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 17:54:36 by hugsbord          #+#    #+#              #
#    Updated: 2021/02/24 10:10:49 by hugsbord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = Cub3D

#INCLUDE = ./includes/cub3d.h

#CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		get_next_line.c \
		check.c \
		cub3d_utils.c \
		key_events.c \
		textures.c \
		init_raycasting.c \
		move.c			\
		error.c	

SRCS_DIR = srcs

INC_DIR = includes

OBJSRCS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

MLX =  libmlx.a
MLX_DIR = minilibx-linux

LIB_MAC = -I /usr/local/include -L /usr/local/lib -lmlx -lm -framework OpenGL -framework Appkit

CC = clang

all : $(NAME)

#$(NAMELIB):
#	make -C ./libft
#	cp ./libft/$(NAMELIB)

$(NAME): $(OBJSRCS) #$(NAMELIB) $(OBJSRCS)
	make -C libft
	clang -I $(DIR_I_LIB) -L $(DIR_LIB) -o $(NAME) $(OBJSRCS) $(LIBS)

%.o: %.c
	clang $(FLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJSRCS) #$(OBJS_BONUS)
	make clean -C ./libft

fclean: clean
#	make fclean -C ./libft
	rm -rf $(NAME)
#	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)

.PHONY:		fclean, clean, re, all
