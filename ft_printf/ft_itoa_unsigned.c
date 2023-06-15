/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:17:18 by dmkael            #+#    #+#             */
/*   Updated: 2023/06/07 15:15:14 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*conversion_unsigned(unsigned int n, int digit);

char	*ft_itoa_unsigned(unsigned int n)
{
	int				digit;
	unsigned int	temp_n;
	char			*result;

	temp_n = n;
	digit = 0;
	while (temp_n != 0)
	{
		digit++;
		temp_n /= 10;
	}
	if (n == 0)
	{
		result = (char *)malloc(sizeof(char) * 2);
		if (result == NULL)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	else
		return (conversion_unsigned(n, digit));
}

static char	*conversion_unsigned(unsigned int n, int digit)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (digit + 1));
	if (result == NULL)
		return (NULL);
	result[digit--] = '\0';
	while (n != 0)
	{
		result[digit--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
