/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:38:21 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_case1(t_fdf *fdf, t_map *map, int r, int c);
static void	draw_case2(t_fdf *fdf, t_map *map, int r, int c);
static void	draw_case3(t_fdf *fdf, t_map *map, int r, int c);
static void	draw_case4(t_fdf *fdf, t_map *map, int r, int c);
extern void	draw_one_point(t_fdf *fdf, t_map *map, int r, int c);
extern void	draw_case5(t_fdf *fdf, t_map *map, int r, int c);
extern void	draw_case6(t_fdf *fdf, t_map *map, int r, int c);
extern void	draw_case7(t_fdf *fdf, t_map *map, int r, int c);
extern void	draw_case8(t_fdf *fdf, t_map *map, int r, int c);

void	draw(t_fdf *fdf, t_map *map)
{
	if (225 < fdf->dtheta || fdf->dtheta <= 45)
	{
		if (315 < fdf->dphi || fdf->dphi <= 45)
			draw_case1(fdf, map, 0, 0);
		else if (45 < fdf->dphi && fdf->dphi <= 135)
			draw_case2(fdf, map, 0, 0);
		else if (135 < fdf->dphi && fdf->dphi <= 225)
			draw_case3(fdf, map, 0, 0);
		else
			draw_case4(fdf, map, 0, 0);
	}
	else
	{
		if (315 < fdf->dphi || fdf->dphi <= 45)
			draw_case5(fdf, map, 0, 0);
		else if (45 < fdf->dphi && fdf->dphi <= 135)
			draw_case6(fdf, map, 0, 0);
		else if (135 < fdf->dphi && fdf->dphi <= 225)
			draw_case7(fdf, map, 0, 0);
		else
			draw_case8(fdf, map, 0, 0);
	}
}

static void	draw_case1(t_fdf *fdf, t_map *map, int r, int c)
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

static void	draw_case2(t_fdf *fdf, t_map *map, int r, int c)
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

static void	draw_case3(t_fdf *fdf, t_map *map, int r, int c)
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

static void	draw_case4(t_fdf *fdf, t_map *map, int r, int c)
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
