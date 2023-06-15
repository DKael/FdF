/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:16:59 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:14:42 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_percent(t_pdata *data)
{
	if (data->flag & MINUS_FLAG)
	{
		write_increase(data, "\045", 1);
		if (data->width != 0)
			print_blank(data, data->width - 1);
	}
	else
	{
		if (data->width != 0)
			print_blank(data, data->width - 1);
		write_increase(data, "\045", 1);
	}
}
