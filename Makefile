# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 19:26:48 by joesanto          #+#    #+#              #
#    Updated: 2025/10/18 16:18:57 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRCS_DIR=srcs
SRCS=ft_printf.c parsers.c types_config.c convert_types.c
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
	git clone git@github.com:joelsantossouza/$(shell basename $(dir $@)).git $(dir $@)
	make -C $(dir $@)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(dir $(LIBS))
	rm -f $(NAME)

re: fclean all
