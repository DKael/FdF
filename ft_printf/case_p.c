/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:16:57 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:14:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	p_with_minus(t_pdata *data, int len, char *addr);
static void	p_without_minus(t_pdata *data, int len, char *addr);

void	case_p(t_pdata *data)
{
	void	*ptr;
	int		len;
	char	*addr;

	ptr = va_arg(data->arg, void *);
	addr = ft_itoa_ptr(ptr);
	len = ft_strlen(addr);
	if (data->flag & MINUS_FLAG)
		p_with_minus(data, len, addr);
	else
		p_without_minus(data, len, addr);
	free(addr);
}

static void	p_with_minus(t_pdata *data, int len, char *addr)
{
	write_increase(data, "0x", 2);
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, addr, len);
	if (data->width != 0)
	{
		if (len > data->precision)
			print_blank(data, data->width - len - 2);
		else
			print_blank(data, data->width - data->precision - 2);
	}
}

static void	p_without_minus(t_pdata *data, int len, char *addr)
{
	if (data->flag & ZERO_FLAG && data->precision == 0)
	{
		write_increase(data, "0x", 2);
		if (data->width != 0)
			print_zero(data, data->width - len - 2);
	}
	else
	{
		if (data->width != 0)
		{
			if (len > data->precision)
				print_blank(data, data->width - len - 2);
			else
				print_blank(data, data->width - data->precision - 2);
		}
		write_increase(data, "0x", 2);
		if (data->precision != 0)
			print_zero(data, data->precision - len);
	}
	write_increase(data, addr, len);
}
