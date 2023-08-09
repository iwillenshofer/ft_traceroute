# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwillens <iwillens@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 15:22:29 by iwillens          #+#    #+#              #
#    Updated: 2023/08/09 01:06:57 by iwillens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# *** Main Definitions                                                         #
# **************************************************************************** #

NAME = ft_traceroute

CC = gcc
CCFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRC_DIR = ./srcs
OBJ_DIR = ./build
INC_DIR = ./includes

SRCS = ${SRC_DIR}/main.c \
		${SRC_DIR}/print/usage.c \
		${SRC_DIR}/print/help.c \
		${SRC_DIR}/print/debug.c \
		${SRC_DIR}/parser/options.c \
		${SRC_DIR}/parser/parser.c \
		${SRC_DIR}/parser/handlers.c \
		${SRC_DIR}/out/packet.c \
		${SRC_DIR}/out/send.c \
		${SRC_DIR}/in/print.c \
		${SRC_DIR}/in/receive.c \
		${SRC_DIR}/common/time.c \
		${SRC_DIR}/common/checksum.c \
		${SRC_DIR}/core/address.c \
		${SRC_DIR}/core/setup.c \
		${SRC_DIR}/core/socket.c \
		${SRC_DIR}/core/trace.c



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

${NAME}: ${LIBFT} ${OBJS} Makefile
	@gcc ${CCFLAGS} ${OBJS}  -L./srcs/libft -lft -o ${NAME}
	@echo "\033[96m${NAME} is built. \033[0m"


${OBJ_DIR}/%.o: $(SRC_DIR)/%.c ${LIBFT} Makefile
	@mkdir -p ${@D}
	@${CC} ${CCFLAGS} -MMD -c $< -I ${INC_DIR} -I${LIBFT_DIR} -o $@


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
