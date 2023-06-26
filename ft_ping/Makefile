# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igorwillenshofer <igorwillenshofer@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/06/26 14:36:09 by igorwillens      ###   ########.fr        #
=======
#    Updated: 2023/06/14 10:04:34 by iwillens         ###   ########.fr        #
>>>>>>> 9cbf17f137ce183b7bb9b37a862f2ebe26e36598
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = ft_ping

CC = gcc
CCFLAGS = -Wall -Werror -Wextra

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes
INCLUDES = ${INC_DIR}/ft_ping.h

SRCS = ${SRC_DIR}/main.c

OBJS = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS})

DEPENDS = $(patsubst %.o, %.d, ${OBJS})

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
HOST_FILE = ${OBJ_DIR}/.${HOSTTYPE}

# **************************************************************************** #
# *** Libft Definitions                                                        #
# **************************************************************************** #
LIBFT_DIR = ./srcs/libft
LIBFT = ${LIBFT_DIR}/libft.a

# **************************************************************************** #
# *** Main Rules                                                               #
# **************************************************************************** #

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS} ${INCLUDES} Makefile ${HOST_FILE}
	@gcc ${CCFLAGS} ${OBJS}  -L./srcs/libft -lft -o ${NAME}
	@rm -f ${SYMLINK}
	@echo "\033[96m${NAME} is built. \033[0m"
	
${OBJ_DIR}/%.o: $(SRC_DIR)/%.c ${INC_DIR} ${INCLUDES} Makefile ${HOST_FILE}
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CCFLAGS} -MMD -c $< -I. -I ${INC_DIR} -I${LIBFT_DIR} -o $@

${HOST_FILE}:
	@mkdir -p ${OBJ_DIR}
	@touch .${HOSTTYPE}

run: all
	./${NAME}

# **************************************************************************** #
# *** Libft Rules                                                              #
# **************************************************************************** #

${LIBFT}:
	@make -s -C ${LIBFT_DIR}

# **************************************************************************** #
# *** Common Rules                                                             #
# **************************************************************************** #
clean:
	@rm -rf ${OBJ_DIR}
	@make  -s -C ${LIBFT_DIR} clean

fclean: clean
	@rm -rf ./${NAME}
	@make  -s -C ${LIBFT_DIR} fclean

re: fclean all

-include $(DEPENDS)
