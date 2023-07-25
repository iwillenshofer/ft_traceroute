# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/07/25 23:17:41 by iwillens         ###   ########.fr        #
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
		${SRC_DIR}/endianess.c \
		${SRC_DIR}/checksum.c \
		${SRC_DIR}/socket.c \
		${SRC_DIR}/address.c \
		${SRC_DIR}/setup.c \
		${SRC_DIR}/print.c \
		${SRC_DIR}/error.c \
		${SRC_DIR}/ping.c \
		${SRC_DIR}/ping_in.c \
		${SRC_DIR}/ping_out.c \
		${SRC_DIR}/duplicate.c \
		${SRC_DIR}/time.c \
		${SRC_DIR}/parser/options.c \
		${SRC_DIR}/parser/parser.c \
		${SRC_DIR}/parser/handlers.c


BONUS_SRCS = ${SRC_DIR}/bonus/new.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)_$(shell uname -n)
endif
HOST_FILE = ${OBJ_DIR}/.host_${HOSTTYPE}

COMPILE_BONUS = false
BUILD_FILE = ${OBJ_DIR}/.build_release
ifneq (,$(filter bonus,$(MAKECMDGOALS)))
	COMPILE_BONUS = true
	BUILD_FILE = ${OBJ_DIR}/.build_bonus
	SRCS += $(BONUS_SRCS)
	CCFLAGS += -DBONUS
endif


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
ifneq (true,$(COMPILE_BONUS))
	@echo "\033[96m${NAME} is built. \033[0m"
else
	@echo "\033[92m${NAME} [bonus] is built. \033[0m"
endif

${OBJ_DIR}/%.o: $(SRC_DIR)/%.c ${INC_DIR} ${INCLUDES} Makefile ${HOST_FILE} ${BUILD_FILE}
	@mkdir -p ${@D}
ifeq (true,$(COMPILE_BONUS))
	@mkdir -p ${OBJ_DIR}/bonus
endif
	@${CC} ${CCFLAGS} -MMD -c $< -I. -I ${INC_DIR} -I${LIBFT_DIR} -o $@

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
