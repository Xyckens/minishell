# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvieira <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 17:21:26 by fvieira           #+#    #+#              #
#    Updated: 2023/02/02 21:55:26 by fvieira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra -I. 

LIBFT = ./libft/libft.a

SRC = main.c \
		export.c \
		set_new_env.c \
		unset.c \
		parser.c \
		append.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)
		echo "OBJ deleted"

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)
		echo "$(NAME) deleted"

re: fclean all

.SILENT:

.PHONY: all, clean, fclean, re
