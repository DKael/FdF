/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:24:50 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:34 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_one_point(t_fdf *fdf, t_map *map, int r, int c)
{
	if (in_window(fdf, map->map[r][c]) == TRUE)
	{
		if (fdf->color_mode == 0)
			mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
				map->map[r][c].ry2d, map->map[r][c].color.color);
		else
			mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
				map->map[r][c].ry2d,
				fdf->contour_color[(int)(map->map[r][c].z
					- map->smallest_z)].color);
	}
}

void	draw_case5(t_fdf *fdf, t_map *map, int r, int c)
{
	r = map->row;
	while (--r >= 0)
	{
		c = map->col;
		while (--c > 0)
		{
			draw_one_point(fdf, map, r, c);
			if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]))
				draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
			if (r > 0)
			{
				if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]))
					draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
				if (!is_flat(map->map[r][c], map->map[r][c - 1],
					map->map[r - 1][c], map->map[r - 1][c - 1]))
					draw_line_diagonal(fdf, map, r - 1, c - 1);
			}
		}
		if (r > 0)
		{
			if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]))
				draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
		}
	}
}

void	draw_case6(t_fdf *fdf, t_map *map, int r, int c)
{
	c = map->col;
	while (--c >= 0)
	{
		r = -1;
		while (++r < map->row - 1)
		{
			draw_one_point(fdf, map, r, c);
			if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]))
				draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
			if (c > 0)
			{
				if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]))
					draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
				if (!is_flat(map->map[r][c], map->map[r + 1][c],
					map->map[r][c - 1], map->map[r + 1][c - 1]))
					draw_line_diagonal(fdf, map, r, c - 1);
			}
		}
		if (c > 0)
		{
			if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]))
				draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
		}
	}
}

void	draw_case7(t_fdf *fdf, t_map *map, int r, int c)
{
	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col - 1)
		{
			draw_one_point(fdf, map, r, c);
			if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]))
				draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
			if (r < map->row - 1)
			{
				if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]))
					draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
				if (!is_flat(map->map[r][c], map->map[r][c + 1],
					map->map[r + 1][c], map->map[r + 1][c + 1]))
					draw_line_diagonal(fdf, map, r, c);
			}
		}
		if (r < map->row - 1)
		{
			if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]))
				draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
		}
	}
}

void	draw_case8(t_fdf *fdf, t_map *map, int r, int c)
{
	c = -1;
	while (++c < map->col)
	{
		r = map->row;
		while (--r > 0)
		{
			draw_one_point(fdf, map, r, c);
			if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]))
				draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
			if (c < map->col - 1)
			{
				if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]))
					draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
				if (!is_flat(map->map[r][c], map->map[r][c + 1],
					map->map[r - 1][c], map->map[r - 1][c + 1]))
					draw_line_diagonal(fdf, map, r - 1, c);
			}
		}
		if (c < map->col - 1)
		{
			if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]))
				draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
		}
	}
}
