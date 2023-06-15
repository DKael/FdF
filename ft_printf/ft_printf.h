/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:25 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/12 15:36:04 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define SHARP_FLAG	1
# define BLANK_FLAG	2
# define MINUS_FLAG	4
# define PLUS_FLAG	8
# define ZERO_FLAG	16
# define PRECISION	32

# define TRUE 1
# define FALSE 0

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef int	t_bool;

typedef struct s_pdata
{
	va_list			arg;
	int				idx;
	int				head;
	int				print_count;
	int				flag;
	int				width;
	int				precision;
	unsigned int	unum;
	int				fd;
}	t_pdata;

typedef struct s_suffix
{
	char	*suffix;
	int		suffix_len;
}	t_suffix;

int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
void	case_c(t_pdata *data);
void	case_s(t_pdata *data);
void	case_p(t_pdata *data);
void	case_d_and_i(t_pdata *data);
void	case_u(t_pdata *data);
void	case_x(t_pdata *data, char x_chr);
void	case_percent(t_pdata *data);
void	init(t_pdata *data);
t_bool	flags_check(char input);
void	print_blank(t_pdata *data, int size);
void	print_zero(t_pdata *data, int size);
char	*ft_itoa_hex(unsigned int n, char chr_x);
char	*ft_itoa_ptr(void *ptr);
char	*ft_itoa_unsigned(unsigned int n);
void	write_increase(t_pdata *data, char *to_write, int len);
#endif
