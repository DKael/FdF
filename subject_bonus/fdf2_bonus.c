/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 20:01:28 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	calc_win_size2(t_map *map);

void	convert_point(t_map *map)
{
	int	r;
	int	c;

	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x = (map->col / 2) * -1 + c;
			map->map[r][c].y = (map->row / 2) * -1 + r;
			map->map[r][c].x2d = (map->map[r][c].x - map->map[r][c].y) * ISO_X;
			map->map[r][c].y2d = (map->map[r][c].x + map->map[r][c].y) * ISO_Y - map->map[r][c].z;;
		}
	} 
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

void	get_rotated_point(t_map *map, double dtheta, double dphi)
{
	int	r;
	int	c;
	t_point	temp1;
	t_point temp2;
	t_angle	theta;
	t_angle	phi;

	theta = calc_angle_func(dtheta);
	phi = calc_angle_func(dphi);
	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			temp1.x = map->map[r][c].x * phi.cos - map->map[r][c].y * phi.sin;
			temp1.y = map->map[r][c].x * phi.sin + map->map[r][c].y * phi.cos;
			temp1.z = map->map[r][c].z;
			temp2.x = (1.0 + theta.cos) / 2.0 * temp1.x + (theta.cos - 1.0) / 2.0 * temp1.y + (1.0 / sqrt(2.0)) * theta.sin * temp1.z;
			temp2.y = (theta.cos - 1.0) / 2.0 * temp1.x + (1.0 + theta.cos) / 2.0 * temp1.y + (1.0 / sqrt(2.0)) * theta.sin * temp1.z;
			temp2.z = theta.cos * temp1.z - (1.0 / sqrt(2.0)) * theta.sin * temp1.x + - (1.0 / sqrt(2.0)) * theta.sin * temp1.y;
			map->map[r][c].x2d = (temp2.x - temp2.y) * ISO_X;
			map->map[r][c].y2d = (temp2.x + temp2.y) * ISO_Y - temp2.z;
		}
	}
}

void	calc_win_size(t_map *map)
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

t_bool	in_window(t_fdf *fdf, t_point p)
{
	if (0 <= p.rx2d + fdf->x2d_move
		&& p.rx2d+ fdf->x2d_move < fdf->win_size_x
		&& 0 <= p.ry2d + fdf->y2d_move
		&& p.ry2d + fdf->y2d_move < fdf->win_size_y)
		return (TRUE);
	else
		return (FALSE);
}

void	draw(t_fdf *fdf, t_map *map)
{
	int	r;
	int	c;

	if (225 < fdf->dtheta || fdf->dtheta <= 45)
	{
		if (315 < fdf->dphi || fdf->dphi <= 45)
		{
			r = -1;
			while (++r < map->row)
			{
				c = -1;
				while (++c < map->col - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
					if (r < map->row - 1)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r + 1][c], map->map[r + 1][c + 1]))
							draw_line_diagonal(fdf, map, r, c);
					}
				}
				if (r < map->row - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
				}
				
			}
		}
		else if (45 < fdf->dphi && fdf->dphi <= 135)
		{
			c = -1;
			while (++c < map->col)
			{
				r = map->row;
				while (--r > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
					if (c < map->col - 1)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r - 1][c], map->map[r - 1][c + 1]))
							draw_line_diagonal(fdf, map, r - 1, c);
					}
				}
				if (c < map->col - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
				}
			}
		}
		else if (135 < fdf->dphi && fdf->dphi <= 225)
		{
			r = map->row;
			while (--r >= 0)
			{
				c = map->col;
				while (--c > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
					if (r > 0)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c - 1],
							map->map[r - 1][c], map->map[r - 1][c - 1]))
							draw_line_diagonal(fdf, map, r - 1, c - 1);
					}
				}
				if (r > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
				}
			}
		}
		else
		{
			c = map->col;
			while (--c >= 0)
			{
				r = -1;
				while (++r < map->row - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
					if (c > 0)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
						if (!is_flat(map->map[r][c], map->map[r + 1][c],
							map->map[r][c - 1], map->map[r + 1][c - 1]))
							draw_line_diagonal(fdf, map, r, c - 1);
					}
				}
				if (c > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
				}
			}
		}
	}
	else
	{
		if (315 < fdf->dphi || fdf->dphi <= 45)
		{
			r = map->row;
			while (--r >= 0)
			{
				c = map->col;
				while (--c > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
					if (r > 0)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c - 1],
							map->map[r - 1][c], map->map[r - 1][c - 1]))
							draw_line_diagonal(fdf, map, r - 1, c - 1);
					}
				}
				if (r > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
				}
			}
		}
		else if (45 < fdf->dphi && fdf->dphi <= 135)
		{
			c = map->col;
			while (--c >= 0)
			{
				r = -1;
				while (++r < map->row - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
					if (c > 0)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
						if (!is_flat(map->map[r][c], map->map[r + 1][c],
							map->map[r][c - 1], map->map[r + 1][c - 1]))
							draw_line_diagonal(fdf, map, r, c - 1);
					}
				}
				if (c > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
				}
			}
		}
		else if (135 < fdf->dphi && fdf->dphi <= 225)
		{
			r = -1;
			while (++r < map->row)
			{
				c = -1;
				while (++c < map->col - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
					if (r < map->row - 1)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r + 1][c], map->map[r + 1][c + 1]))
							draw_line_diagonal(fdf, map, r, c);
					}
				}
				if (r < map->row - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
				}
			}
		}
		else
		{
			c = -1;
			while (++c < map->col)
			{
				r = map->row;
				while (--r > 0)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE)
						mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
					if (c < map->col - 1)
					{
						if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r - 1][c], map->map[r - 1][c + 1]))
							draw_line_diagonal(fdf, map, r - 1, c);
					}
				}
				if (c < map->col - 1)
				{
					if (in_window(fdf, map->map[r][c]) == TRUE || in_window(fdf, map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
				}
			}
		}
	}
}

void	screen_clear(t_fdf *fdf, int image_num)
{
	char	*dst;
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->win_size_y)
	{
		x = -1;
		while (++x < fdf->win_size_x)
		{
			dst = fdf->img_addr[image_num] + y * fdf->size_line[image_num] + x * (fdf->bpp[image_num] / 8);
			*(unsigned int *)dst = 0x00000000;
		}
	}
}
