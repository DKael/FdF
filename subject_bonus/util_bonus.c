/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:36:24 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/23 18:06:03 by hyungdki         ###   ########.fr       */
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

void	fdf_init(t_fdf *fdf, t_map *map)
{
	fdf->mlx_ptr = T_NULL;
	fdf->win_ptr = T_NULL;
	fdf->img_ptr[0] = T_NULL;
	fdf->img_addr[0] = T_NULL;
	fdf->img_ptr[1] = T_NULL;
	fdf->img_addr[1] = T_NULL;
	fdf->win_size_x = WINDOW_SIZE_X;
	fdf->win_size_y = WINDOW_SIZE_Y;
	fdf->map_ptr = map;
	fdf->x2d_move = 0;
	fdf->y2d_move = 0;
	fdf->flag = 0;
	fdf->move_speed = 10;
	fdf->rot_speed = 1;
	fdf->dtheta = 0;
	fdf->dphi = 0;
	fdf->l_mouse_clk = FALSE;
	fdf->r_mouse_clk = FALSE;
	fdf->old_x = -1;
	fdf->old_y = -1;
	fdf->cur_image = 0;
	fdf->projection = 0;
	fdf->color_mode = 0;
	fdf->contour_color = T_NULL;
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
