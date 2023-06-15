/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:06 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:14:53 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	u_with_minus(t_pdata *data, int len, char *unum_str);
static void	u_without_minus(t_pdata *data, int len, char *unum_str);

void	case_u(t_pdata *data)
{
	unsigned int	unum;
	int				len;
	char			*unum_str;

	unum = va_arg(data->arg, unsigned int);
	unum_str = ft_itoa_unsigned(unum);
	len = ft_strlen(unum_str);
	if (data->flag & MINUS_FLAG)
		u_with_minus(data, len, unum_str);
	else
		u_without_minus(data, len, unum_str);
	free(unum_str);
}

static void	u_with_minus(t_pdata *data, int len, char *unum_str)
{
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, unum_str, len);
	if (data->width != 0)
	{
		if (len > data->precision)
			print_blank(data, data->width - len);
		else
			print_blank(data, data->width - data->precision);
	}
}

static void	u_without_minus(t_pdata *data, int len, char *unum_str)
{
	if (data->flag & ZERO_FLAG && data->precision == 0)
	{
		if (data->width != 0)
			print_zero(data, data->width - len);
	}
	else
	{
		if (data->width != 0)
		{
			if (len > data->precision)
				print_blank(data, data->width - len);
			else
				print_blank(data, data->width - data->precision);
		}
	}
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, unum_str, len);
}
