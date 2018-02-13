#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/13 19:56:11 by akupriia          #+#    #+#              #
#    Updated: 2018/01/18 20:00:48 by akupriia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRC = 	libft/ft_putchar.c \
		libft/ft_atoi.c \
		libft/ft_strstr.c \
		libft/ft_strcat.c \
		libft/ft_strncat.c \
		libft/ft_memmove.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_strlcat.c \
		libft/ft_strchr.c \
		libft/ft_strrchr.c \
		libft/ft_strnstr.c \
		libft/ft_memalloc.c \
		libft/ft_memdel.c \
		libft/ft_strnew.c \
		libft/ft_strdel.c \
		libft/ft_strclr.c \
		libft/ft_striter.c \
		libft/ft_striteri.c \
		libft/ft_strmap.c \
		libft/ft_strmapi.c \
		libft/ft_strequ.c \
		libft/ft_strnequ.c \
		libft/ft_strsub.c \
		libft/ft_strjoin.c \
		libft/ft_strtrim.c \
		libft/ft_strsplit.c \
		libft/ft_itoa.c \
		libft/ft_lstnew.c \
		libft/ft_lstdelone.c \
		libft/ft_lstdel.c \
		libft/ft_lstadd.c \
		libft/ft_lstiter.c \
		libft/ft_lstmap.c \
		libft/ft_lstsplit.c \
		libft/ft_swap.c \
		libft/ft_sqrt.c \
		libft/ft_noregcmp.c \
		libft/ft_nbrlen.c \
		libft/ft_dectooct.c \
		libft/ft_power.c \
		libft/ft_itoa_base.c \
		libft/ft_putendl.c \
		libft/ft_putnbr.c \
		libft/ft_putstr.c \
		libft/ft_strcmp.c \
		libft/ft_strcpy.c \
		libft/ft_strdup.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strncpy.c \
		libft/ft_isalpha.c \
		libft/ft_isdigit.c \
		libft/ft_isalnum.c \
		libft/ft_isascii.c \
		libft/ft_isprint.c \
		libft/ft_toupper.c \
		libft/ft_tolower.c \
		libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_putendl_fd.c \
		libft/ft_putnbr_fd.c \
		libft/ft_memset.c \
		libft/ft_bzero.c \
		libft/ft_memcpy.c \
		libft/ft_memccpy.c \
		libft/libft.h \
		libft/ft_itoa_base_u.c \
		libft/ft_nbrlen_u.c \
		src/char_nil_sth.c \
		src/dig_min.c \
		src/dig_plus.c \
		src/dig_plusnil.c \
		src/dig_pluswidth.c \
		src/file1.c \
		src/handle_char.c \
		src/handle_dig.c \
		src/handle_dig1.c \
		src/handle_pointer.c \
		src/handle_string.c \
		src/parse_flags.c \
		src/parse_spec.c \
		src/parse_specif.c \
		src/print_char.c \
		src/print_uni.c \
		src/print_unsigned.c \
		src/stfunc.c \
		src/str_min.c \
		src/str_nil.c \
		src/str_nil_sth.c \
		src/struni1.c \
		src/uns_nil.c \
		src/ft_printf.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f libft/*.o src/*.o
	/bin/rm -f libft/*.gch src/*.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
