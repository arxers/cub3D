# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 17:49:27 by jaslim            #+#    #+#              #
#    Updated: 2024/08/14 18:30:29 by jaslim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRC =	src/ft_atoi.c \
	src/ft_bzero.c \
	src/ft_calloc.c \
	src/ft_isalnum.c \
	src/ft_isalpha.c \
	src/ft_isascii.c \
	src/ft_isdigit.c \
	src/ft_isprint.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_memcpy.c \
	src/ft_memmove.c \
	src/ft_memset.c \
	src/ft_strchr.c \
	src/ft_strdup.c \
	src/ft_strlcat.c \
	src/ft_strlcpy.c \
	src/ft_strlen.c \
	src/ft_strncmp.c \
	src/ft_strnstr.c \
	src/ft_strrchr.c \
	src/ft_tolower.c \
	src/ft_toupper.c \
	src/ft_putchar_fd.c \
	src/ft_putstr_fd.c \
	src/ft_putendl_fd.c \
	src/ft_putnbr_fd.c \
	src/ft_substr.c \
	src/ft_strjoin.c \
	src/ft_strtrim.c \
	src/ft_strmapi.c \
	src/ft_striteri.c \
	src/ft_itoa.c \
	src/ft_split.c \
	src/ft_lstnew.c \
	src/ft_lstadd_front.c \
	src/ft_lstsize.c \
	src/ft_lstlast.c \
	src/ft_lstadd_back.c \
	src/ft_lstdelone.c \
	src/ft_lstdel_char.c \
	src/ft_lstclear.c \
	src/ft_lstiter.c \
	src/ft_lstmap.c \
	src/ft_free.c \
	src/ft_atol.c \
	src/ft_strcmp.c \
	src/ft_count_digits.c \
	src/ft_isspace.c \
	src/ft_lst_to_arr.c \
	src/ft_strtok.c \
	src/ft_count_strings.c \
	src/ft_print_fd.c \
	src/ft_only_c.c \
	src/ft_abs.c \
	src_printf/ft_printf.c \
	src_printf/ft_printf_alnum.c \
	src_printf/ft_printf_hex.c \
	src_printf/ft_dprintf.c \
	src_printf/ft_sprintf.c \
	src_gnl/get_next_line.c \
	src_gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
