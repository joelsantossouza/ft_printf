# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 19:26:48 by joesanto          #+#    #+#              #
#    Updated: 2025/10/21 10:09:43 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

TYPES_CONFIG=$(addprefix types_config/, int_config.c uint_config.c str_config.c \
ptr_config.c chr_config.c perc_config.c)

SRCS_DIR=srcs
SRCS=ft_printf.c parsers.c convert_types.c $(TYPES_CONFIG)
OBJS=$(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))
HEADERS=ft_printf.h

LIBS_DIR=libs
LIB_SRCS=$(addprefix libft/, ft_static_ultoa_base.c ft_static_ltoa_base.c \
ft_putchar_fd.c ft_memset.c ft_max.c ft_strlen.c ft_putstr_fd.c ft_atol_base.c \
ft_strncmp.c ft_strlcpy.c ft_strnlen.c ft_strchr.c ft_strcmp.c ft_isspace.c \
ft_udigit_count.c ft_nbrlen.c ft_abs.c ft_memchr.c ft_mempset.c)

LIBS_OBJS=$(addprefix $(LIBS_DIR)/, $(LIB_SRCS:.c=.o))

INCLUDES=$(addprefix -I, . $(LIBS_DIR)/libft)

CC=cc
FLAGS=-Wall -Wextra -Werror -g -Wmissing-declarations -Wmissing-prototypes
AR=ar rcs

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBS_OBJS) $(OBJS)
	$(AR) $@ $^

$(LIBS_DIR)/%.o:
	git clone git@github.com:joelsantossouza/$(shell basename $(dir $@)).git $(dir $@)
	make -C $(dir $@)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(LIBS_DIR)
	rm -f $(NAME)

re: fclean all
