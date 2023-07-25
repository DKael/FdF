/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_func_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:13 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	get_map_data2(t_map *map);

void	get_map_data(t_map *map)
{
	int	r;
	int	c;

	map->smallest_z = map->map[0][0].z;
	map->largest_z = map->map[0][0].z;
	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			if (map->map[r][c].y2d > map->largest_y2d)
				map->largest_y2d = map->map[r][c].y2d;
			else if (map->map[r][c].y2d < map->smallest_y2d)
				map->smallest_y2d = map->map[r][c].y2d;
			if (map->smallest_z > map->map[r][c].z)
				map->smallest_z = map->map[r][c].z;
			else if (map->largest_z < map->map[r][c].z)
				map->largest_z = map->map[r][c].z;
		}
	}
	map->largest_x2d = map->map[0][map->col - 1].x2d;
	map->smallest_x2d = map->map[map->row - 1][0].x2d;
	get_map_data2(map);
}

static void	get_map_data2(t_map *map)
{
	map->len_x2d = map->largest_x2d - map->smallest_x2d;
	map->len_y2d = map->largest_y2d - map->smallest_y2d;
	if (map->len_x2d * WINDOW_SIZE_Y > map->len_y2d * WINDOW_SIZE_X)
		map->basic_len = WINDOW_SIZE_X / map->len_x2d;
	else
		map->basic_len = WINDOW_SIZE_Y / map->len_y2d;
	map->basic_len_index = (int)(log10(map->basic_len) / ZOOM_LOG10 + 0.5);
	if (map->basic_len_index >= 100)
		map->basic_len_index = 100;
	else if (map->basic_len_index <= -10)
		map->basic_len_index = -10;
	map->basic_len = pow(ZOOM_VALUE, map->basic_len_index);
	map->midpoint_x2d = WINDOW_SIZE_X / 2;
	map->midpoint_y2d = WINDOW_SIZE_Y / 2
		- (int)((map->largest_y2d + map->smallest_y2d) * map->basic_len) / 2;
	map->prj_ptr.x = 0.0;
	map->prj_ptr.y = map->row * -3.0;
	map->prj_ptr.z = (map->largest_z + map->smallest_z) / 2.0;
}

t_bool	in_window(t_fdf *fdf, t_point p)
{
	if (0 <= p.rx2d + fdf->x2d_move
		&& p.rx2d + fdf->x2d_move < fdf->win_size_x
		&& 0 <= p.ry2d + fdf->y2d_move
		&& p.ry2d + fdf->y2d_move < fdf->win_size_y)
		return (TRUE);
	else
		return (FALSE);
}

void	screen_clear(t_fdf *fdf, int image_num)
{
	char	*dst;
	int		x;
	int		y;

	y = -1;
	while (++y < fdf->win_size_y)
	{
		x = -1;
		while (++x < fdf->win_size_x)
		{
			dst = fdf->img_addr[image_num] + y
				* fdf->size_line[image_num] + x
				* (fdf->bpp[image_num] / 8);
			*(unsigned int *)dst = 0x00000000;
		}
	}
}
