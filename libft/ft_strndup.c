/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:37:48 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/04 17:45:18 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(char *src, size_t n)
{
	size_t	index;
	char	*replica;

	replica = (char *)malloc(sizeof(char) * (n + 1));
	if (replica == NULL)
		return (NULL);
	index = 0;
	while (src[index] != '\0' && index < n)
	{
		replica[index] = src[index];
		index++;
	}
	replica[index] = '\0';
	return (replica);
}
