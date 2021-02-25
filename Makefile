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

LIBS = -lmlx -lm -framework OpenGL -framework Appkit

DIR_I_LIB = /usr/local/include/

DIR_LIB = /usr/local/lib/

NAME = cub3D

#INCLUDE = ./includes/cub3d.h

#CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		get_next_line.c \
		check.c \
		cub3d_utils.c \

#SRCS_BONUS = 

SRCS_DIR = srcs

INC_DIR = include

OBJSRCS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

MLX =  libmlx.dylib

CC = clang

all : $(NAME)

$(NAMELIB):
	make -C ./libft
	cp ./libft/$(NAMELIB)

$(NAME): $(NAMELIB) $(OBJSRCS)
	ar -x libft.a
	clang $(CFLAGS) -I $(DIR_I_LIB) -L $(DIR_LIB) -o $(NAME) $(OBJSRCS) $(LIBS)

#	@ar rc $(NAME) $(OBJS)

#$(MLX):
#	@$(MAKE) -C mlx
#	@mv mlx/$(MLX)

#$(NAME): $(NAMELIB) $(OBJSRCS)
#	$(CC) $(OBJSRCS) -o $(NAME) $(LIBS)

clean:
	rm -rf $(OBJSRCS) $(OBJS_BONUS)
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
#	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)

.PHONY:		fclean, clean, re, all
