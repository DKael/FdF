/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 20:27:56 by hyungdki          #+#    #+#             */
/*   Updated: 2023/05/04 17:38:59 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	size_t	src_length;
	size_t	index;
	char	*replica;

	src_length = ft_strlen(src);
	replica = (char *)malloc(sizeof(char) * (src_length + 1));
	if (replica == NULL)
		return (NULL);
	index = 0;
	while (src[index] != '\0')
	{
		replica[index] = src[index];
		index++;
	}
	replica[index] = '\0';
	return (replica);
}
