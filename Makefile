# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: s72h <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/23 12:17:59 by s72h              #+#    #+#              #
#    Updated: 2020/05/26 10:31:03 by s72h             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = -lmlx -lm -framework OpenGL -framework Appkit -lm
#MLX = gcc -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext <fichier(s) .c>

DIR_I_LIB = /usr/local/include/

DIR_LIB = /usr/local/lib/

NAME = cub3D

INCLUDE = ./includes/cub3d.h

#CFLAGS = -Wall -Wextra -Werror

SRCS = main.c

#SRCS_BONUS = 

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

MLX =  libmlx.dylib

all : $(NAME)

$(NAMELIB):
	@make -C ./libft
	@cp ./libft/$(NAMELIB)

$(NAME): $(NAMELIB) $(OBJS) $(OBJS_BONUS) #$(MLX)
	@ar -x libft.a
	@gcc $(CFLAGS) -I $(DIR_I_LIB) -L $(DIR_LIB) -o $(NAME) $(OBJS) $(LIBS)

	@ar rc $(NAME) $(OBJS)

#$(MLX):
#	@$(MAKE) -C mlx
#	@mv mlx/$(MLX)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)

.PHONY:		fclean clean re all
