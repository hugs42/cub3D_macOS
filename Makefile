# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 17:54:36 by hugsbord          #+#    #+#              #
#    Updated: 2021/01/14 18:15:06 by hugsbord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = -lmlx -lm -framework OpenGL -framework Appkit# -lm

DIR_I_LIB = /usr/local/include/

DIR_LIB = /usr/local/lib/

NAME = cub3D

INCLUDE = ./includes/cub3d.h

#CFLAGS = -Wall -Wextra -Werror

SRCS = main.c /
		check.c

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
	@clang $(CFLAGS) -I $(DIR_I_LIB) -L $(DIR_LIB) -o $(NAME) $(OBJS) $(LIBS)

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
#	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)

.PHONY:		fclean clean re all
