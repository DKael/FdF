/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_calc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:30:36 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 19:17:03 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

void	get_rotated_point(t_map *map, double dtheta, double dphi)
{
	int		r;
	int		c;
	t_point	temp;
	t_angle	tht;
	t_angle	phi;

	tht = calc_angle_func(dtheta);
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
			map->map[r][c].tx = (1.0 + tht.cos) / 2.0 * temp.x + (tht.cos - 1.0)
				/ 2.0 * temp.y + (1.0 / sqrt(2.0)) * tht.sin * temp.z;
			map->map[r][c].ty = (tht.cos - 1.0) / 2.0 * temp.x + (1.0 + tht.cos)
				/ 2.0 * temp.y + (1.0 / sqrt(2.0)) * tht.sin * temp.z;
			map->map[r][c].tz = tht.cos * temp.z - (1.0 / sqrt(2.0))
				* tht.sin * temp.x + - (1.0 / sqrt(2.0)) * tht.sin * temp.y;
		}
	}
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
			map->map[r][c].x2d = (map->map[r][c].tx
					- map->map[r][c].ty) * ISO_X;
			map->map[r][c].y2d = (map->map[r][c].tx
					+ map->map[r][c].ty - map->map[r][c].tz * 2) * ISO_Y;
		}
	}
}

void	perspective_projection(t_map *map)
{
	int		r;
	int		c;
	double	ratio;

	r = -1;
	while (++r < map->row)
	{
		c = -1;
		while (++c < map->col)
		{
			ratio = (map->map[r][c].ty - map->prj_ptr.y)
				/ (map->row / 2.0 - map->prj_ptr.y);
			map->map[r][c].px = map->map[r][c].tx * ratio;
			map->map[r][c].py = map->map[r][c].ty;
			map->map[r][c].pz = map->map[r][c].tz * ratio;
			map->map[r][c].x2d = (map->map[r][c].px
					- map->map[r][c].py) * ISO_X;
			map->map[r][c].y2d = (map->map[r][c].px
					+ map->map[r][c].py - map->map[r][c].pz * 2) * ISO_Y;
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
			map->map[r][c].rx2d = (int)(map->map[r][c].x2d
					* map->basic_len + 0.5) + map->midpoint_x2d;
			map->map[r][c].ry2d = (int)(map->map[r][c].y2d
					* map->basic_len + 0.5) + map->midpoint_y2d;
		}
	}
}
