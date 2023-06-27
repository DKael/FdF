# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 20:30:42 by hyungdki          #+#    #+#              #
#    Updated: 2023/06/27 13:28:40 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./subject_mandatory/main.c	\
		./subject_mandatory/draw_diagonal1.c  \
		./subject_mandatory/draw_diagonal2.c  \
		./subject_mandatory/draw1.c  \
		./subject_mandatory/draw2.c  \
		./subject_mandatory/draw3.c  \
		./subject_mandatory/error.c  \
		./subject_mandatory/event.c  \
		./subject_mandatory/fdf1.c  \
		./subject_mandatory/fdf2.c  \
		./subject_mandatory/map_parsing.c  \
		./subject_mandatory/util.c  \
		
OBJS = 	${SRCS:.c=.o}

SRCS_BONUS =	./subject_bonus/main_bonus.c	\
				./subject_bonus/draw_diagonal1_bonus.c  \
				./subject_bonus/draw_diagonal2_bonus.c  \
				./subject_bonus/draw1_bonus.c  \
				./subject_bonus/draw2_bonus.c  \
				./subject_bonus/draw3_bonus.c  \
				./subject_bonus/error_bonus.c  \
				./subject_bonus/event_bonus.c  \
				./subject_bonus/fdf1_bonus.c  \
				./subject_bonus/fdf2_bonus.c  \
				./subject_bonus/map_parsing_bonus.c  \
				./subject_bonus/util_bonus.c  \

OBJS_BONUS = 	${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = fdf

LIBFT_DIR = libft

LIBGNL_DIR = gnl

LIBFTPRINTF_DIR = ft_printf

MLX_DIR = minilibx

MLX_DYLIB = libmlx.dylib

WITH_BONUS = 0

ifeq ($(WITH_BONUS),1)
	TOTAL_OBJS = ${OBJS_BONUS}
else
	TOTAL_OBJS = ${OBJS}
endif

LDFLAGS = -L./libft -lft -L./gnl -lgnl -L./ft_printf -lftprintf -L. -lmlx

${NAME} : ${TOTAL_OBJS}
	make -C ${LIBFT_DIR} all
	make -C ${LIBGNL_DIR} all
	make -C ${LIBFTPRINTF_DIR} all
	make -C ${MLX_DIR} all
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
