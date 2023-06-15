/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:09 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:14:58 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	x_with_minus(t_pdata *data, int len, char *hex, t_suffix *sfx);
static void	x_without_minus(t_pdata *data, int len, char *hex, t_suffix *sfx);

void	case_x(t_pdata *data, char x_chr)
{
	unsigned int	unum;
	int				len;
	char			*hex;
	t_suffix		sfx;

	unum = va_arg(data->arg, unsigned int);
	data->unum = unum;
	hex = ft_itoa_hex(unum, x_chr);
	len = ft_strlen(hex);
	sfx.suffix_len = 0;
	if (data->flag & SHARP_FLAG && unum != 0)
	{
		sfx.suffix = "0x";
		if (x_chr == 'X')
			sfx.suffix = "0X";
		sfx.suffix_len = 2;
	}
	if (data->flag & MINUS_FLAG)
		x_with_minus(data, len, hex, &sfx);
	else
		x_without_minus(data, len, hex, &sfx);
	free(hex);
}

static void	x_with_minus(t_pdata *data, int len, char *hex, t_suffix *sfx)
{
	if (data->flag & SHARP_FLAG && data->unum != 0)
		write_increase(data, sfx->suffix, sfx->suffix_len);
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, hex, len);
	if (data->width != 0)
	{
		if (len > data->precision)
			print_blank(data, data->width - len - sfx->suffix_len);
		else
			print_blank(data, data->width - data->precision - sfx->suffix_len);
	}
}

static void	x_without_minus(t_pdata *data, int len, char *hex, t_suffix *sfx)
{
	if (data->flag & ZERO_FLAG && data->precision == 0)
	{
		if (data->flag & SHARP_FLAG && data->unum != 0)
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
		if (data->flag & SHARP_FLAG && data->unum != 0)
			write_increase(data, sfx->suffix, sfx->suffix_len);
	}
	if (data->precision != 0)
		print_zero(data, data->precision - len);
	write_increase(data, hex, len);
}
