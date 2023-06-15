/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_d_and_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:16:54 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:15:56 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	d_sign(int flag, int num, t_suffix *sfx);
static void	minus(t_pdata *data, int len, char *num_str, t_suffix *sfx);
static void	no_minus(t_pdata *data, int len, char *num_str, t_suffix *sfx);

void	case_d_and_i(t_pdata *data)
{
	int			num;
	int			len;
	char		*num_str;
	t_suffix	sfx;

	num = va_arg(data->arg, int);
	d_sign(data->flag, num, &sfx);
	if (num >= 0)
		num_str = ft_itoa_unsigned(num);
	else
		num_str = ft_itoa_unsigned(num * -1);
	len = ft_strlen(num_str);
	if (data->flag & BLANK_FLAG && num > 0)
	{
		data->width -= 1;
		write_increase(data, " ", 1);
	}
	if (data->flag & MINUS_FLAG)
		minus(data, len, num_str, &sfx);
	else
		no_minus(data, len, num_str, &sfx);
	free(num_str);
}

static void	d_sign(int flag, int num, t_suffix *sfx)
{
	sfx->suffix = "";
	sfx->suffix_len = 0;
	if (flag & PLUS_FLAG && num > 0)
	{
		sfx->suffix = "+";
		sfx->suffix_len = 1;
	}
	else if (num < 0)
	{
		sfx->suffix = "-";
		sfx->suffix_len = 1;
	}
}

static void	minus(t_pdata *data, int len, char *num_str, t_suffix *sfx)
{
	write_increase(data, sfx->suffix, sfx->suffix_len);
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, num_str, len);
	if (data->width != 0)
	{
		if (len > data->precision)
			print_blank(data, data->width - len - sfx->suffix_len);
		else
			print_blank(data, data->width - data->precision - sfx->suffix_len);
	}
}

static void	no_minus(t_pdata *data, int len, char *num_str, t_suffix *sfx)
{
	if (data->flag & ZERO_FLAG && data->precision == 0)
	{
		write_increase(data, sfx->suffix, sfx->suffix_len);
		if (data->width != 0)
			print_zero(data, data->width - len - sfx->suffix_len);
	}
	else
	{
		if (data->width != 0)
		{
			if (len > data->precision)
				print_blank(data, data->width - len - sfx->suffix_len);
			else
				print_blank(data,
					data->width - data->precision - sfx->suffix_len);
		}
		write_increase(data, sfx->suffix, sfx->suffix_len);
	}
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, num_str, len);
}
