# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alanter <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/18 11:26:55 by alanter           #+#    #+#              #
#    Updated: 2018/12/10 15:28:39 by alanter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## PROJECT ########################

NAME = asm 

########################## OS ###########################

OS := $(shell uname)

######################### COLOR #########################

BLUE = \033[1;34m
RED = \033[8m\033[1;31m
GREEN = \033[32m
NORMAL = \033[0m
LINE_ERASER = \n\033[1A\033[0K\r

########################## STR ##########################

STR_SUCCESS = $(GREEN)SUCCESS$(BLUE).\n$(NORMAL)

######################### FLAGS #########################

ifeq ($(OS),Darwin)
	FLAGS_DEFAULT = -g3 -Wall -Werror -Wextra
else 
	FLAGS_DEFAULT = -Wall -Werror -Wextra
endif
FLAGS_LIB = -L$(LIBFT_PATH) -lft -lncurses

####################### LIBRARIES #######################

LIBFT_PATH = ../libft/
LIBFT = $(LIBFT_PATH)libft.a

######################## COMMANDS #######################

CC = gcc
MAKE = /usr/bin/make
MOVE = /bin/mv
RM = /bin/rm -f
MKDIR = /bin/mkdir

######################## INCLUDES #######################

INC_DIR = ./includes/ ../libft/includes
INC_PREF = -I
INC_FILES = ./includes/asm.h ./includes/op.h
INC = $(addprefix $(INC_PREF), $(INC_DIR))

######################## SOURCES ########################

SRC_PATH = ./srcs/
SRC_FILES =	asm.c \
			pars_liste.c \
			pars_file.c \
			write_to_fd.c \
			param_in_inst.c \
			inst_in_list.c \
			find_label.c \
			op.c \
			label_func.c \
			melting_pot.c \
			keep_instruction.c \
			header_in_list.c \
			free.c \
			utile.c \
			utile2.c \
			utile3.c \
			check_error.c
			
SRCS = $(addprefix $(SRC_PATH), $(SRC_FILES))

######################## OBJECTS ########################

OBJ_PATH = ./objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
	OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
	OBJ_DIR = objs

######################### RULES #########################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(INC_FILES)
	@printf "$(LINE_ERASER)$(RED)$@: $(BLUE)Objects compilation: $(STR_SUCCESS)"
	@printf "$(RED)$@: $(BLUE)Compiling project: $(NORMAL)"
	@$(CC) $(FLAGS_DEFAULT) $(OBJS) $(FLAGS_LIB) -o $@
	@cp ./$(NAME) ../
	@printf "$(STR_SUCCESS)"
	@printf "$(RED)$@: $(GREEN)project ready.$(NORMAL)\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@printf "$(RED)$(NAME): $(BLUE)Cleaning objects: $(NORMAL)"
	@$(RM) $(OBJS)
	@printf "$(STR_SUCCESS)"

fclean: clean
	@printf "$(RED)$(NAME): $(BLUE)Cleaning project: $(NORMAL)"
	@$(RM) ../$(NAME) $(NAME)
	@rm -f $(LIBFT) 
	@printf "$(STR_SUCCESS)"

re: $(MAKE) fclean 
	$(MAKE) alll

$(OBJ_DIR):
	@printf "$(RED)$(NAME): $(BLUE)Create objects folder: $(NORMAL)"
	@mkdir -p $@
	@printf "$(STR_SUCCESS)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@printf "$(LINE_ERASER)$(RED)$(NAME): $(BLUE)Compiling: $(NORMAL)\"$@\"."
	@$(CC) -o $@ $< $(FLAGS_DEFAULT) -c $(INC)

.PHONY: all clean fclean re
