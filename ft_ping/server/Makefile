# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/07/06 13:09:22 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions for the SERVER                                          #
# **************************************************************************** #

NAME = ft_server

CC = gcc
CCFLAGS = -Wall -Werror -Wextra

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes
INCLUDES = ${INC_DIR}/ft_server.h

SRCS = ${SRC_DIR}/main.c

OBJS = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS})

DEPENDS = $(patsubst ${OBJ_DIR}/%.o, ${OBJ_DIR}/%.d, ${OBJS})

# **************************************************************************** #
# *** Main Rules                                                               #
# **************************************************************************** #

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS} ${INCLUDES} Makefile
	gcc ${CCFLAGS} ${OBJS} -o ${NAME}
	@echo "\033[90m${NAME} is built. \033[0m"

${OBJ_DIR}/%.o: $(SRC_DIR)/%.c ${INC_DIR} ${INCLUDES} Makefile
	@mkdir -p ${OBJ_DIR}
	@${CC} ${CCFLAGS} -MMD -c $< -I. -I ${INC_DIR} -o $@


run: all
	./${NAME} 8080

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

fclean: clean
	@rm -rf ./${NAME}

re: fclean all	

-include $(DEPENDS)
