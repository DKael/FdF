/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 21:56:05 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	calc_win_size2(t_map *map);

void	convert_point(t_map *map)
{
	int	r;
	int	c;
	double ralpha;
	double rbeta;

	r = -1;
	ralpha = ALPHA_START * RADIAN;
	rbeta = BETA_START * RADIAN;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x = (map->row / 2) * -1 + c;
			map->map[r][c].y = (map->col / 2) * -1 + r;
			map->map[r][c].x2d = map->map[r][c].x * cos(rbeta)
						- map->map[r][c].z * sin(rbeta);
			map->map[r][c].y2d = (map->map[r][c].x * sin(ralpha) * sin(rbeta)
						+ map->map[r][c].y * cos(ralpha) 
						+ map->map[r][c].z * sin(ralpha) * cos(rbeta)) * 1.1;
		}
	}
}

void	rotate_point(t_map *map, double alpha, double beta)
{
	int	r;
	int	c;
	double ralpha;
	double rbeta;

	r = -1;
	ralpha = alpha * RADIAN;
	rbeta = beta * RADIAN;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x2d = map->map[r][c].x * cos(rbeta) - map->map[r][c].z * sin(rbeta);
			map->map[r][c].y2d = (map->map[r][c].x * sin(ralpha) * sin(rbeta) + map->map[r][c].y * cos(ralpha) + map->map[r][c].z * sin(ralpha) * cos(rbeta)) * 1.1;
		}
	}
}

void	calc_win_size1(t_map *map)
{
	int	r;
	int	c;

	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			if (map->map[r][c].x2d > map->largest_x2d)
				map->largest_x2d = map->map[r][c].x2d;
			else if (map->map[r][c].x2d < map->smallest_x2d)
				map->smallest_x2d = map->map[r][c].x2d;
			if (map->map[r][c].y2d > map->largest_y2d)
				map->largest_y2d = map->map[r][c].y2d;
			else if (map->map[r][c].y2d < map->smallest_y2d)
				map->smallest_y2d = map->map[r][c].y2d;
		}
	}
	calc_win_size2(map);
}

static void	calc_win_size2(t_map *map)
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
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].rx2d = (int)(map->map[r][c].x2d * map->basic_len + 0.5)
				+ map->midpoint_x2d;
			map->map[r][c].ry2d = (int)(map->map[r][c].y2d * map->basic_len + 0.5)
				+ map->midpoint_y2d;
		}
	}
}

void	draw(t_fdf *fdf, t_map *map)
{
	int	r;
	int	c;

	r = -1;
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

void	screen_clear(t_fdf *fdf)
{
	char	*dst;
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->win_size_y)
	{
		dst = fdf->img_addr + y * fdf->size_line;
		x = -1;
		while (++x < fdf->win_size_x)
		{
			dst += fdf->bpp / 8;
			*(unsigned int *)dst = 0x00000000;
		}
	}
}