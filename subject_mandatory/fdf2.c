/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/26 21:04:45 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	convert_point(t_map *map)
{
	int	r;
	int	c;

	r = -1;
	c = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x = (map->row / 2) * -1 + c;
			map->map[r][c].y = (map->col / 2) * -1 + r;
			map->map[r][c].x_2d = (map->map[r][c].x - map->map[r][c].y) * ISO_X;
			if (map->map[r][c].x_2d > map->largest_x_2d)
				map->largest_x_2d = map->map[r][c].x_2d;
			else if (map->map[r][c].x_2d < map->smallest_x_2d)
				map->smallest_x_2d = map->map[r][c].x_2d;
			map->map[r][c].y_2d = (map->map[r][c].x + map->map[r][c].y) * ISO_Y
				- map->map[r][c].z;
			if (map->map[r][c].y_2d > map->largest_y_2d)
				map->largest_y_2d = map->map[r][c].y_2d;
			else if (map->map[r][c].y_2d < map->smallest_y_2d)
				map->smallest_y_2d = map->map[r][c].y_2d;
		}
	}
}

void	calc_win_size(t_map *map)
{
	map->len_x_2d = map->largest_x_2d - map->smallest_x_2d;
	map->len_y_2d = map->largest_y_2d - map->smallest_y_2d;
	if (map->len_x_2d * ((double)WINDOW_SIZE_Y / WINDOW_SIZE_X) > map->len_y_2d)
		map->basic_len = WINDOW_SIZE_X / map->len_x_2d;
	else
		map->basic_len = WINDOW_SIZE_Y / map->len_y_2d;
	map->midpoint_x_2d = WINDOW_SIZE_X / 2
		- (int)((map->largest_x_2d + map->smallest_x_2d) * map->basic_len) / 2;
	map->midpoint_y_2d = WINDOW_SIZE_Y / 2
		- (int)((map->largest_y_2d + map->smallest_y_2d) * map->basic_len) / 2;
}

void	enlarge_image(t_map *map)
{
	int	r;
	int	c;

	r = -1;
	c = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x_2d = map->map[r][c].x_2d * map->basic_len;
			map->map[r][c].rx_2d = (int)(map->map[r][c].x_2d + 0.5)
				+ map->midpoint_x_2d;
			map->map[r][c].y_2d = map->map[r][c].y_2d * map->basic_len;
			map->map[r][c].ry_2d = (int)(map->map[r][c].y_2d + 0.5)
				+ map->midpoint_y_2d;
		}
	}
}

void	draw(t_fdf *fdf, t_map *map)
{
	int	r;
	int	c;

	r = -1;
	c = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col - 1)
		{
			mlx_pixel_put_at_mem(fdf, map->map[r][c].rx_2d,
				map->map[r][c].ry_2d, map->map[r][c].color.color);
			draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
			if (r < map->row - 1)
			{
				draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
				if (!is_flat(map->map[r][c], map->map[r][c + 1],
					map->map[r + 1][c], map->map[r + 1][c + 1]))
					draw_line_diagonal(fdf, map, r, c);
			}
		}
		if (r < map->row - 1)
			draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
	}
}
