# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 19:26:48 by joesanto          #+#    #+#              #
#    Updated: 2025/10/15 15:40:26 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRCS_DIR=srcs
SRCS=ft_printf.c convertions.c parsers.c
OBJS=$(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

CC=cc
FLAGS=-Wall -Wextra -Werror -g -Wmissing-declarations -Wmissing-prototypes -O3
AR=ar rcs

LIBS_DIR=libs
LIBS=$(addprefix $(LIBS_DIR)/, libft/libft.a)

HEADERS_DIR=includes
HEADERS=$(addprefix $(HEADERS_DIR)/, libftprintf.h libft.h)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(AR) $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HEADERS_DIR)

%.a:
	git -C $(dir $@) pull
	make bonus -C $(dir $@)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
