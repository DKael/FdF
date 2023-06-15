/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:20 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/12 15:38:00 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_width(const char *format, t_pdata *data);
static void	get_precision(const char *format, t_pdata *data);
static void	format_read(const char *format, t_pdata *data);
static void	format_print(const char *format, t_pdata *data);

int	ft_printf(const char *format, ...)
{
	t_pdata	data;

	va_start(data.arg, format);
	init(&data);
	data.fd = 1;
	while (format[++(data.idx)] != '\0')
	{
		if (format[(data.idx)] == '%')
		{
			format_read(format, &data);
			format_print(format, &data);
			data.head = data.idx + 1;
			data.flag = 0;
			data.precision = 0;
			data.width = 0;
		}
		else
			data.print_count++;
	}
	write(data.fd, &(format[data.head]), data.idx - data.head);
	va_end(data.arg);
	return (data.print_count);
}

void	format_read(const char *format, t_pdata *data)
{
	write(data->fd, &(format[data->head]), data->idx - data->head);
	while (flags_check(format[++(data->idx)]))
	{
		if (format[data->idx] == '#')
			data->flag |= SHARP_FLAG;
		else if (format[data->idx] == ' ')
			data->flag |= BLANK_FLAG;
		else if (format[data->idx] == '-')
			data->flag |= MINUS_FLAG;
		else if (format[data->idx] == '+')
			data->flag |= PLUS_FLAG;
		else if (format[data->idx] == '0')
			data->flag |= ZERO_FLAG;
		else if (ft_isdigit(format[data->idx]))
			get_width(format, data);
		else if (format[data->idx] == '.' )
			get_precision(format, data);
	}
}

static void	get_width(const char *format, t_pdata *data)
{
	data->width = format[data->idx] - '0';
	while (ft_isdigit(format[++(data->idx)]))
		data->width = data->width * 10 + (format[data->idx] - '0');
	data->idx--;
}

static void	get_precision(const char *format, t_pdata *data)
{
	data->precision = 0;
	while (ft_isdigit(format[++(data->idx)]))
		data->precision = data->precision * 10 + (format[data->idx] - '0');
	data->idx--;
}

void	format_print(const char *format, t_pdata *data)
{
	if (format[data->idx] == 'c')
		case_c(data);
	else if (format[data->idx] == 's')
		case_s(data);
	else if (format[data->idx] == 'p')
		case_p(data);
	else if (format[data->idx] == 'd' || format[data->idx] == 'i')
		case_d_and_i(data);
	else if (format[data->idx] == 'u')
		case_u(data);
	else if (format[data->idx] == 'x' || format[data->idx] == 'X')
		case_x(data, format[data->idx]);
	else if (format[data->idx] == '%')
		case_percent(data);
	else
	{
		data->head = data->idx;
		(data->print_count)++;
	}
}
