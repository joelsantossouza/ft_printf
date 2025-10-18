# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 12:13:42 by joesanto          #+#    #+#              #
#    Updated: 2025/10/18 12:33:41 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST=$(patsubst %.c, %, $(SRCS))

SRCS=$(wildcard ft_*_test.c)
OBJS=$(SRCS:.c=.o)
CC=cc
FLAGS=-Wall -Wextra -Werror -g
EXTRA=
LIBS=../libftprintf.a ../libs/libft/libft.a

.SECONDARY: $(OBJS) $(LIBS)

all: $(TEST)

ft_%_test: ft_%_test.o $(LIBS)
	$(CC) $^ -latf-c -o $@

ft_%_test.o: ft_%_test.c
	$(CC) $(FLAGS) $(EXTRA) -c $< -o $@

%.a: 
	make -C $(dir $@)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TEST)

re: fclean all
