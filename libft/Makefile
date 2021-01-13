# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 12:18:47 by hugsbord          #+#    #+#              #
#    Updated: 2020/02/17 12:39:42 by hugsbord         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

HEADERS = libft.h

SRC =	ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c 		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strncmp.c		\
		ft_strlcpy.c 		\
		ft_strlcat.c		\
		ft_strnstr.c		\
		ft_atoi.c			\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_substr.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putnbr_fd.c		\
		ft_putendl_fd.c		\
		ft_swap.c			\
		ft_isspace.c		\
		ft_islower.c		\
		ft_isupper.c		\
		ft_strrev.c			\
		ft_putnstr_fd.c	

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(HEADERS) $(OBJ)
	@echo "Libft creation :"
	@ar rc $(NAME) $(OBJ)
	@echo "$(NAME) created ..."
	@ranlib $(NAME)
	@echo "$(NAME) correctly indexed"

bonus : $(OBJ) $(OBJ_B)
	@echo "Bonus creation :"
	@ar rc  $(NAME) $(OBJ) $(OBJ_B)
	@echo "Done ..."
	@ranlib $(NAME)
	@echo "$(NAME) with bonus correctly indexed"

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_B)
	@echo "OBJ (.o) removed"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all, clean, fclean, re
