# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 12:26:47 by jlebard           #+#    #+#              #
#    Updated: 2024/07/17 12:39:44 by jlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/getters_and_setters.c ./src/handle_mutex_threads.c ./src/init_datas \
./src/main.c ./src/parsing.c ./src/simulation.c ./src/utils.c
OBJ = $(SRC:.c=.o)
CLEAN = rm -rf
FCLEAN = rm -f

all: $(NAME)

%.o: %.c	
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(CLEAN) $(OBJ)

fclean:
	$(FCLEAN) $(NAME)

re:
	fclean all

.PHONY: re all fclean clean
