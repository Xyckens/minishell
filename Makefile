# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvieira <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 17:21:26 by fvieira           #+#    #+#              #
#    Updated: 2023/02/17 20:12:36 by fvieira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra -I. -g 

LIBFT = ./libft/libft.a

SRC = main.c \
		set_new_env.c \
		parser.c \
		append.c \
		executables.c \
		delimit.c \
		echo.c \
		path_related.c \
		sanitize.c \
		ft_export.c \
		pelicaseaspas.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) --no-print-directory -C ./libft
	echo "./minishell created"
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

run: re
	./minishell

.SILENT:

.PHONY: all, clean, fclean, re
