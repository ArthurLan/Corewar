# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clecalie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 11:07:11 by clecalie          #+#    #+#              #
#    Updated: 2018/11/21 17:43:59 by clecalie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = 	get_next_line.c \
		ft_ctos.c \
		ft_strtolower.c \
		ft_itoa_base.c \
		ft_atoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strndup.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_bzero.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strrev.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_list_push_back.c \
		ft_list_push_front.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_atoi_base.c \
		ft_split_whitespaces.c \
		cpt_letter.c \
		cpt_word.c \
		ft_strncpy2.c \
		 ./ft_printf/ft_printf.c \
		 ./ft_printf/apply_flag.c \
		 ./ft_printf/ft_printf.util.c \
		 ./ft_printf/handle_flags.c \
		 ./ft_printf/handle_letters_dxou.c \
		 ./ft_printf/handle_letters_sc.c \
		 ./ft_printf/manipulation.c \
		 ./ft_printf/precision.c \
		 ./ft_printf/wchartoasc.c \
		 ./ft_printf/replacestr.c \
		 ./ft_printf/ft_atol.c \
		 ./ft_printf/ft_uintmaxtoa.c \
		 ./ft_printf/ft_intmaxtoa.c \
		 ./ft_printf/ft_uintmaxtoa_base.c \
		 ./ft_printf/ft_intmaxtoa_base.c \
		 ./ft_printf/ft_ulltoa.c \
		 ./ft_printf/ft_ulltoa_base.c \
		 ./ft_printf/handle_sharp.c \
		 ./ft_printf/handle_neg.c \
		 ./ft_printf/handle_plus.c \
		 ./ft_printf/handle_digit.c \
		 ./ft_printf/handle_space.c \
		 ./ft_printf/handle_zero.c

OBJ = $(SRCS:.c=.o)
OBJ_WITHOUT_DIR = $(notdir $(OBJ))

FLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc ./$(NAME) $(OBJ_WITHOUT_DIR)

%.o: %.c
	@gcc -c $< $(FLAGS) -I includes/

clean:
	@rm -f $(OBJ_WITHOUT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
