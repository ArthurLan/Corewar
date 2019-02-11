# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alanter <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/18 11:26:55 by alanter           #+#    #+#              #
#    Updated: 2019/01/30 14:25:55 by alanter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## PROJECT ########################

COREWAR = corewar 
ASM = asm

######################## PATHS ########################

COREWAR_PATH = ./make_corewar
ASM_PATH = ./make_asm

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

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

######################## COMMANDS #######################

CC = gcc
MAKE = /usr/bin/make
MOVE = /bin/mv
RM = /bin/rm -f
MKDIR = /bin/mkdir

######################## INCLUDES #######################

# INC_DIR = ./includes/ ../libft/includes
# INC_PREF = -I
# INC_FILES = ./includes/corewar.h ./includes/op.h
# INC = $(addprefix $(INC_PREF), $(INC_DIR))

######################### RULES #########################

all:
	@$(MAKE) -C $(COREWAR_PATH)
	@$(MAKE) -C $(ASM_PATH)
	@$(RM) -r *.dSYM

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(RM) -r *.dSYM
	@$(MAKE) clean -C $(COREWAR_PATH)
	@$(MAKE) clean -C $(ASM_PATH)

fclean:
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(MAKE) fclean -C $(COREWAR_PATH)
	@$(MAKE) fclean -C $(ASM_PATH)

re: $(MAKE) fclean 
	$(MAKE) all

.PHONY: all clean fclean re
