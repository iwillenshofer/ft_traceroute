# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/07/29 22:42:10 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = ft_ping

CC = gcc
CCFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes
INCLUDES = ${INC_DIR}/ft_ping.h

SRCS = ${SRC_DIR}/main.c \
		${SRC_DIR}/socket.c \
		${SRC_DIR}/address.c \
		${SRC_DIR}/setup.c \
		${SRC_DIR}/ping.c \
		${SRC_DIR}/in/ping_in.c \
		${SRC_DIR}/in/noecho.c \
		${SRC_DIR}/in/print.c \
		${SRC_DIR}/out/ping_out.c \
		${SRC_DIR}/out/packet.c \
		${SRC_DIR}/common/checksum.c \
		${SRC_DIR}/common/duplicate.c \
		${SRC_DIR}/common/time.c \
		${SRC_DIR}/print/usage.c \
		${SRC_DIR}/print/help.c \
		${SRC_DIR}/parser/options.c \
		${SRC_DIR}/parser/parser.c \
		${SRC_DIR}/parser/handlers.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)_$(shell uname -n)
endif
HOST_FILE = ${OBJ_DIR}/.host_${HOSTTYPE}

OBJS = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS})

DEPENDS = $(patsubst ${OBJ_DIR}/%.o, ${OBJ_DIR}/%.d, ${OBJS})

# **************************************************************************** #
# *** Libft Definitions                                                        #
# **************************************************************************** #
LIBFT_DIR = ./srcs/libft
LIBFT = ${LIBFT_DIR}/libft.a

# **************************************************************************** #
# *** Main Rules                                                               #
# **************************************************************************** #

all: ${NAME}

bonus: ${NAME}

${NAME}: ${LIBFT} ${OBJS} ${INCLUDES} Makefile ${HOST_FILE} ${BUILD_FILE}
	gcc ${CCFLAGS} ${OBJS}  -L./srcs/libft -lft -o ${NAME}
	@echo "\033[96m${NAME} is built. \033[0m"


${OBJ_DIR}/%.o: $(SRC_DIR)/%.c ${INC_DIR} ${INCLUDES} Makefile ${HOST_FILE} ${BUILD_FILE}
	@mkdir -p ${@D}
	${CC} ${CCFLAGS} -MMD -c $< -I. -I ${INC_DIR} -I${LIBFT_DIR} -o $@

${HOST_FILE}:
	@rm -rf ${OBJ_DIR}
	@mkdir -p ${OBJ_DIR}
	@touch ${HOST_FILE}

${BUILD_FILE}:
	@rm -rf ${OBJ_DIR}/.build_*
	@mkdir -p ${OBJ_DIR}
	@touch ${BUILD_FILE}
	@echo "\033[99m${BUILD_FILE} is built. \033[0m"

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
