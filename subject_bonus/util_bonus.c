/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:36:24 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 20:21:24 by hyungdki         ###   ########.fr       */
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

void	fdf_init(t_fdf *fdf, t_map *map)
{
	fdf->mlx_ptr = T_NULL;
	fdf->win_ptr = T_NULL;
	fdf->img_ptr = T_NULL;
	fdf->img_addr = T_NULL;
	fdf->win_size_x = WINDOW_SIZE_X;
	fdf->win_size_y = WINDOW_SIZE_Y;
	fdf->map_ptr = map;
	fdf->x2d_move = 0;
	fdf->y2d_move = 0;
	fdf->loc_change = FALSE;
	fdf->zoom_change = FALSE;
	fdf->rotate_change = FALSE;
	fdf->move_value = 10;
	fdf->alpha = 35.264;
	fdf->beta = 45.0;
}

void	map_init(t_map *map)
{
	map->map = T_NULL;
	map->row = 0;
	map->col = 0;
	map->fd = -1;
	map->largest_x2d = (WINDOW_SIZE_X / 2) * -1;
	map->largest_y2d = (WINDOW_SIZE_Y / 2) * -1;
	map->smallest_x2d = WINDOW_SIZE_X / 2;
	map->smallest_y2d = WINDOW_SIZE_Y / 2;
}
