# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 13:30:01 by hyungdki          #+#    #+#              #
#    Updated: 2023/06/17 20:29:25 by hyungdki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c \
		ft_fprintf.c \
		ft_printf_utils.c \
		case_c.c \
		case_d_and_i.c \
		case_p.c \
		case_percent.c \
		case_s.c \
		case_u.c \
		case_x.c \
		ft_itoa_hex.c \
		ft_itoa_ptr.c \
		ft_itoa_unsigned.c

OBJS = 	${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

TOTAL_OBJS = ${OBJS}

${NAME} : ${TOTAL_OBJS}
		ar -rsc $@ $^
	
%.o :%.c
	@${CC} ${CFLAGS} -c -I. $< -o $@

all : ${NAME}

clean:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean: 
	@$(MAKE) clean
	rm -f  ${NAME}

re: 
	@$(MAKE) fclean
	@$(MAKE) all

bonus:
	@make all

.PHONY: all clean fclean re bonus
