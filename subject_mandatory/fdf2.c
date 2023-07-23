/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/04 16:39:47 by hyungdki         ###   ########.fr       */
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
			map->map[r][c].x2d = (map->map[r][c].x - map->map[r][c].y) * ISO_X;
			if (map->map[r][c].x2d > map->largest_x2d)
				map->largest_x2d = map->map[r][c].x2d;
			else if (map->map[r][c].x2d < map->smallest_x2d)
				map->smallest_x2d = map->map[r][c].x2d;
			map->map[r][c].y2d = (map->map[r][c].x + map->map[r][c].y
				- map->map[r][c].z) * ISO_Y;
			if (map->map[r][c].y2d > map->largest_y2d)
				map->largest_y2d = map->map[r][c].y2d;
			else if (map->map[r][c].y2d < map->smallest_y2d)
				map->smallest_y2d = map->map[r][c].y2d;
		}
	}
}

void	calc_win_size(t_map *map)
{
	map->len_x2d = map->largest_x2d - map->smallest_x2d;
	map->len_y2d = map->largest_y2d - map->smallest_y2d;
	if (map->len_x2d * ((double)WINDOW_SIZE_Y / WINDOW_SIZE_X) > map->len_y2d)
		map->basic_len = WINDOW_SIZE_X / map->len_x2d;
	else
		map->basic_len = WINDOW_SIZE_Y / map->len_y2d;
	map->midpoint_x2d = WINDOW_SIZE_X / 2
		- (int)((map->largest_x2d + map->smallest_x2d) * map->basic_len) / 2;
	map->midpoint_y2d = WINDOW_SIZE_Y / 2
		- (int)((map->largest_y2d + map->smallest_y2d) * map->basic_len) / 2;
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
			map->map[r][c].x2d = map->map[r][c].x2d * map->basic_len;
			map->map[r][c].rx2d = (int)(map->map[r][c].x2d + 0.5)
				+ map->midpoint_x2d;
			map->map[r][c].y2d = map->map[r][c].y2d * map->basic_len;
			map->map[r][c].ry2d = (int)(map->map[r][c].y2d + 0.5)
				+ map->midpoint_y2d;
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
			mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
				map->map[r][c].ry2d, map->map[r][c].color.color);
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
