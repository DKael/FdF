/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:13:40 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/07 17:08:46 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int	str_index;
	int	find_index;

	if (to_find[0] == '\0')
		return (str);
	str_index = 0;
	while (str[str_index] != '\0')
	{
		if (str[str_index] == to_find[0])
		{
			find_index = 1;
			while (to_find[find_index] != '\0')
			{
				if (str[str_index + find_index] != to_find[find_index])
					break ;
				find_index++;
			}
			if (to_find[find_index] == '\0')
				return (&str[str_index]);
		}
		str_index++;
	}
	return (0);
}
