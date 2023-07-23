/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:49:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/23 18:03:43 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	get_map_data2(t_map *map);

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
			map->map[r][c].tx = map->map[r][c].x;
			map->map[r][c].ty = map->map[r][c].y;
			map->map[r][c].tz = map->map[r][c].z;
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
	t_point	temp;
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
			temp.x = map->map[r][c].x * phi.cos - map->map[r][c].y * phi.sin;
			temp.y = map->map[r][c].x * phi.sin + map->map[r][c].y * phi.cos;
			temp.z = map->map[r][c].z;
			map->map[r][c].tx = (1.0 + theta.cos) / 2.0 * temp.x + (theta.cos - 1.0) / 2.0 * temp.y + (1.0 / sqrt(2.0)) * theta.sin * temp.z;
			map->map[r][c].ty = (theta.cos - 1.0) / 2.0 * temp.x + (1.0 + theta.cos) / 2.0 * temp.y + (1.0 / sqrt(2.0)) * theta.sin * temp.z;
			map->map[r][c].tz = theta.cos * temp.z - (1.0 / sqrt(2.0)) * theta.sin * temp.x + - (1.0 / sqrt(2.0)) * theta.sin * temp.y;
		}
	}
}

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

void	isometric_projection(t_map *map)
{
	int	r;
	int	c;

	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			map->map[r][c].x2d = (map->map[r][c].tx - map->map[r][c].ty) * ISO_X;
			map->map[r][c].y2d = (map->map[r][c].tx + map->map[r][c].ty - map->map[r][c].tz * 2) * ISO_Y;
		}
	}
}

void	perspective_projection(t_map *map)
{
	int	r;
	int	c;
	double	ratio;

	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			ratio = (map->map[r][c].ty - map->prj_ptr.y) / (map->row / 2.0 - map->prj_ptr.y);
			map->map[r][c].px = map->map[r][c].tx * ratio;
			map->map[r][c].py = map->map[r][c].ty;
			map->map[r][c].pz = map->map[r][c].tz * ratio;
			map->map[r][c].x2d = (map->map[r][c].px - map->map[r][c].py) * ISO_X;
			map->map[r][c].y2d = (map->map[r][c].px + map->map[r][c].py - map->map[r][c].pz * 2) * ISO_Y;
		}
	}
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

t_bool	should_draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	double	slope;
	int		p1x;
	int		p2x;
	int		p1y;
	int		p2y;

	p1x = p1.rx2d + fdf->x2d_move;
	p2x = p2.rx2d + fdf->x2d_move;
	p1y = p1.ry2d + fdf->y2d_move;
	p2y = p2.ry2d + fdf->y2d_move;
	if (p2x != p1x)
	{
		slope = ((double)(p2y - p1y) / (p2x - p1x));
		if (slope > 0.0)
		{
			if (p2y - p2x * slope < fdf->win_size_y && slope * (fdf->win_size_x - 1 - p2x) + p2y >= 0)
				return (TRUE);
		}
		else if (slope < 0.0)
		{
			if (p2y - slope * p2x >= 0 && slope * (fdf->win_size_x - 1 - p2x) + p2y < fdf->win_size_y)
				return (TRUE);
		}
		else
		{
			if (0 <= p2y && p2y < fdf->win_size_y)
				if (!((p2x < 0 && p1x < 0) || (p2x >= fdf->win_size_x && p1x >= fdf->win_size_x)))
					return (TRUE);
		}
	}
	else
	{
		if (0 <= p2x && p2x < fdf->win_size_x)
			if (!((p2y < 0 && p1y < 0) || (p2y >= fdf->win_size_y && p1y >= fdf->win_size_y)))
				return (TRUE);
	}
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
					{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
					if (r < map->row - 1)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r + 1][c], map->map[r + 1][c + 1]))
							draw_line_diagonal(fdf, map, r, c);
					}
				}
				if (r < map->row - 1)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
					if (c < map->col - 1)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r - 1][c], map->map[r - 1][c + 1]))
							draw_line_diagonal(fdf, map, r - 1, c);
					}
				}
				if (c < map->col - 1)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
					if (r > 0)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c - 1],
							map->map[r - 1][c], map->map[r - 1][c - 1]))
							draw_line_diagonal(fdf, map, r - 1, c - 1);
					}
				}
				if (r > 0)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
					if (c > 0)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
						if (!is_flat(map->map[r][c], map->map[r + 1][c],
							map->map[r][c - 1], map->map[r + 1][c - 1]))
							draw_line_diagonal(fdf, map, r, c - 1);
					}
				}
				if (c > 0)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
					if (r > 0)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c - 1],
							map->map[r - 1][c], map->map[r - 1][c - 1]))
							draw_line_diagonal(fdf, map, r - 1, c - 1);
					}
				}
				if (r > 0)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
					if (c > 0)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c - 1]);
						if (!is_flat(map->map[r][c], map->map[r + 1][c],
							map->map[r][c - 1], map->map[r + 1][c - 1]))
							draw_line_diagonal(fdf, map, r, c - 1);
					}
				}
				if (c > 0)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c - 1]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
					if (r < map->row - 1)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r + 1][c]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r + 1][c], map->map[r + 1][c + 1]))
							draw_line_diagonal(fdf, map, r, c);
					}
				}
				if (r < map->row - 1)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r + 1][c]) == TRUE)
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
						{
						if (fdf->color_mode == 0)
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, map->map[r][c].color.color);
						else
							mlx_pixel_put_at_mem(fdf, map->map[r][c].rx2d,
							map->map[r][c].ry2d, fdf->contour_color[(int)(map->map[r][c].z - map->smallest_z)].color);
					}	
					if (should_draw_line(fdf, map->map[r][c], map->map[r - 1][c]) == TRUE)
						draw_line(fdf, map->map[r][c], map->map[r - 1][c]);
					if (c < map->col - 1)
					{
						if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
							draw_line(fdf, map->map[r][c], map->map[r][c + 1]);
						if (!is_flat(map->map[r][c], map->map[r][c + 1],
							map->map[r - 1][c], map->map[r - 1][c + 1]))
							draw_line_diagonal(fdf, map, r - 1, c);
					}
				}
				if (c < map->col - 1)
				{
					if (should_draw_line(fdf, map->map[r][c], map->map[r][c + 1]) == TRUE)
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
