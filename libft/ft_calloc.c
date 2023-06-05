/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:27:30 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 14:35:48 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	index;
	size_t	total_size;
	void	*result;
	char	*temp_ptr;

	index = 0;
	if (count == 0 || size == 0)
		return (malloc(0));
	total_size = count * size;
	if (ULLONG_MAX / size < count)
		return ((NULL));
	result = malloc(total_size);
	if (result == NULL)
		return (NULL);
	temp_ptr = (char *)result;
	while (index < total_size)
	{
		temp_ptr[index] = 0;
		index++;
	}
	return (result);
}
