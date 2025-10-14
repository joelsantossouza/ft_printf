# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 19:26:48 by joesanto          #+#    #+#              #
#    Updated: 2025/10/14 19:47:01 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRCS=
OBJS=$(SRCS:.c=.o)

CC=cc
FLAGS=-Wall -Wextra -Werror -g -Wmissing-declarations -Wmissing-prototypes -03

LIBS_DIR=libs
LIBS=libft/libft.a

HEADERS_DIR=includes
HEADERS=ft_printf.h

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_DIR)/$(LIBS)
	$(CC) $^ -o $@

%.o: %.c $(HEADERS_DIR)/$(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR)

