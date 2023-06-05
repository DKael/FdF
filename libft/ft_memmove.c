/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:27:49 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/30 14:36:33 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*dst_cptr;
	unsigned char	*src_cptr;

	index = -1;
	dst_cptr = (unsigned char *)dst;
	src_cptr = (unsigned char *)src;
	if (dst != NULL || src != NULL)
	{
		if (src - dst > 0)
		{
			while (++index < len)
				dst_cptr[index] = src_cptr[index];
		}
		else
		{
			while (++index < len)
				dst_cptr[len - index - 1] = src_cptr[len - index - 1];
		}
	}
	return (dst);
}
