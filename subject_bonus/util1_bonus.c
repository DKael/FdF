/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:36:24 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:05 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_2d_array(void **array)
{
	int	idx;

	if (array != T_NULL)
	{
		idx = -1;
		while (array[++idx] != T_NULL)
			free(array[idx]);
		free(array);
		array = T_NULL;
	}
}

unsigned int	hex_str_to_uint(char *str_color)
{
	int				idx;
	unsigned int	result;

	idx = 0;
	result = 0;
	while (str_color[idx] != 'x' && str_color[idx] != 'X')
		idx++;
	while (str_color[++idx] != '\0' && str_color[idx] != '\n')
	{
		if ('0' <= str_color[idx] && str_color[idx] <= '9')
			result = result * 16 + (str_color[idx] - '0');
		else if ('a' <= str_color[idx] && str_color[idx] <= 'f')
			result = result * 16 + (str_color[idx] - 'a') + 10;
		else if ('A' <= str_color[idx] && str_color[idx] <= 'F')
			result = result * 16 + (str_color[idx] - 'A') + 10;
		else
			return (0xFFFFFF);
	}
	return (result);
}

t_bool	is_flat(t_point p1, t_point p2, t_point p3, t_point p4)
{
	if ((p2.x - p1.x == p4.x - p3.x
			&& p2.y - p1.y == p4.y - p3.y
			&& p2.z - p1.z == p4.z - p3.z)
		&& (p1.x - p3.x == p2.x - p4.x
			&& p1.y - p3.y == p2.y - p4.y
			&& p1.z - p3.z == p2.z - p4.z))
		return (TRUE);
	else
		return (FALSE);
}

t_angle	calc_angle_func(int angle)
{
	t_angle	return_value;
	double	radian_angle;

	radian_angle = (double)angle * RADIAN;
	return_value.sin = sin(radian_angle);
	return_value.cos = cos(radian_angle);
	if (angle == 90 || angle == 270)
		return_value.tan = tan(radian_angle);
	else
		return_value.tan = 0;
	return (return_value);
}
