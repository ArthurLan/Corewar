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

NAME = corewar 

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
INC_FILES = ./includes/corewar.h ./includes/op.h
INC = $(addprefix $(INC_PREF), $(INC_DIR))

######################## SOURCES ########################

SRC_PATH = ./srcs/
SRC_FILES =	main.c \
			op.c \
			init_champions.c \
			init_champ_head.c \
			init_arena.c \
			battle.c \
			init_process.c \
			visu.c \
			visu_right.c \
			exec_op.c \
			champs_func.c \
			filter.c \
			exec/get_func.c \
			exec/exec_live.c \
			exec/exec_ld.c \
			exec/exec_st.c \
			exec/exec_add.c \
			exec/exec_sub.c \
			exec/exec_and.c \
			exec/exec_or.c \
			exec/exec_xor.c \
			exec/exec_zjmp.c \
			exec/exec_ldi.c \
			exec/exec_sti.c \
			exec/exec_sti_b.c \
			exec/exec_fork.c \
			exec/exec_lld.c \
			exec/exec_lldi.c \
			exec/exec_lfork.c \
			exec/exec_aff.c \

SRCS = $(addprefix $(SRC_PATH), $(SRC_FILES))

######################## OBJECTS ########################

OBJ_PATH = ./objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
	OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))
	OBJ_DIR = objs objs/exec

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
	@printf "$(STR_SUCCESS)"

re: $(MAKE) fclean 
	$(MAKE) all

$(OBJ_DIR):
	@printf "$(RED)$(NAME): $(BLUE)Create objects folder: $(NORMAL)"
	@mkdir -p $@
	@printf "$(STR_SUCCESS)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@printf "$(LINE_ERASER)$(RED)$(NAME): $(BLUE)Compiling: $(NORMAL)\"$@\"."
	@$(CC) -o $@ $< $(FLAGS_DEFAULT) -c $(INC)

.PHONY: all clean fclean re
