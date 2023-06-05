/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:27:46 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 14:36:24 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*s_ucptr;

	index = -1;
	s_ucptr = (unsigned char *)s;
	while (++index < n)
	{
		if (s_ucptr[index] == (unsigned char)c)
			return ((void *)((size_t)s_ucptr + index));
	}
	return (NULL);
}
