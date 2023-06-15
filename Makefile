# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:30:42 by hyungdki          #+#    #+#              #
#    Updated: 2023/06/12 18:02:00 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c	\
		
OBJS = 	${SRCS:.c=.o}

# SRCS_BONUS =	main_bonus.c	\

# OBJS_BONUS = 	${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = fdf

LIBFT_DIR = libft

LIBGNL_DIR = gnl

LIBFTPRINTF_DIR = ft_printf

MLX_DIR = minilibx

MLX_DYLIB = libmlx.dylib

WITH_BONUS = 0

# ifeq ($(WITH_BONUS),1)
# 	TOTAL_OBJS = ${OBJS_BONUS}
# 	LDFLAGS = -L./libft -L./gnl -lft -lgnl
# else
# 	TOTAL_OBJS = ${OBJS}
# 	LDFLAGS = -L./libft -lft
# endif

TOTAL_OBJS = ${OBJS}

LDFLAGS = -L./libft -lft -L./gnl -lgnl -L./ft_printf -lftprintf -L. -lmlx

# ${NAME} : ${TOTAL_OBJS}
# 		make -C ${LIBFT_DIR} all
# ifeq ($(WITH_BONUS),1)
# 	make -C ${LIBGNL_DIR} all
# endif
# 		${CC} ${CFLAGS} ${LDFLAGS} ${TOTAL_OBJS} -o $@

${NAME} : ${TOTAL_OBJS}
	@make -C ${LIBFT_DIR} all
	@make -C ${LIBGNL_DIR} all
	@make -C ${LIBFTPRINTF_DIR} all
	@make -C ${MLX_DIR} all
	mv ${MLX_DIR}/${MLX_DYLIB} .
	${CC} ${LDFLAGS} ${TOTAL_OBJS} -framework OpenGL -framework Appkit -o $@

%.o :%.c
	${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	make -C ${LIBFT_DIR} fclean
	make -C ${LIBGNL_DIR} fclean
	make -C ${LIBFTPRINTF_DIR} fclean
	make -C ${MLX_DIR} clean
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: 
	make clean
	rm -f ${MLX_DYLIB}
	rm -rf ${NAME}

re: 
	make fclean
	make all

bonus:
	@make WITH_BONUS=1

.PHONY: all clean fclean re bonus
