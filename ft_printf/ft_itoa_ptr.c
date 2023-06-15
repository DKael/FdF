/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:14 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:15:09 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*conversion_ptr(unsigned long long n, int digit);

char	*ft_itoa_ptr(void *ptr)
{
	int					digit;
	unsigned long long	addr;
	unsigned long long	temp_addr;
	char				*result;

	addr = (unsigned long long)ptr;
	temp_addr = addr;
	digit = 0;
	while (temp_addr != 0)
	{
		digit++;
		temp_addr /= 16;
	}
	if (addr == 0)
	{
		result = (char *)malloc(sizeof(char) * 2);
		if (result == NULL)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	else
		return (conversion_ptr(addr, digit));
}

static char	*conversion_ptr(unsigned long long addr, int digit)
{
	char	*result;
	char	*base;

	result = (char *)malloc(sizeof(char) * (digit + 1));
	if (result == NULL)
		return (NULL);
	result[digit--] = '\0';
	base = "0123456789abcdef";
	while (addr != 0)
	{
		result[digit--] = base[(addr % 16)];
		addr /= 16;
	}
	return (result);
}
