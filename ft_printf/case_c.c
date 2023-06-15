/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:16:50 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:15:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_c(t_pdata *data)
{
	char	chr;

	chr = va_arg(data->arg, int);
	if (data->flag & MINUS_FLAG)
	{
		write_increase(data, &chr, 1);
		if (data->width != 0)
		{
			print_blank(data, data->width - 1);
		}
	}
	else
	{
		if (data->width != 0)
		{
			print_blank(data, data->width - 1);
		}
		write_increase(data, &chr, 1);
	}
}
