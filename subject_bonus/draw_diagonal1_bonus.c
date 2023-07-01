/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:48:23 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/01 18:01:12 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_bool	draw_line_diagonal_con1(int z[][2], t_fdf *fdf, int r, int c);
static t_bool	draw_line_diagonal_con2(int z[][2], t_fdf *fdf, int r, int c);
static t_bool	draw_line_diagonal_con3(int z[][2], t_fdf *fdf, int r, int c);
static t_bool	draw_line_diagonal_con4(int z[][2], t_fdf *fdf, int r, int c);
extern t_bool	draw_line_diagonal_con5(int z[][2], t_fdf *fdf, int r, int c);
extern t_bool	draw_line_diagonal_con6(int z[][2], t_fdf *fdf, int r, int c);
extern t_bool	draw_line_diagonal_con7(int z[][2], t_fdf *fdf, int r, int c);
extern t_bool	draw_line_diagonal_con8(int z[][2], t_fdf *fdf, int r, int c);

void	draw_line_diagonal(t_fdf *fdf, t_map *map, int r, int c)
{
	int	z[2][2];

	z[0][0] = map->map[r][c].z;
	z[0][1] = map->map[r][c + 1].z;
	z[1][0] = map->map[r + 1][c].z;
	z[1][1] = map->map[r + 1][c + 1].z;
	if (draw_line_diagonal_con1(z, fdf, r, c))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (draw_line_diagonal_con2(z, fdf, r, c))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con3(z, fdf, r, c))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (draw_line_diagonal_con4(z, fdf, r, c))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con5(z, fdf, r, c))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (draw_line_diagonal_con6(z, fdf, r, c))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con5(z, fdf, r, c))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con6(z, fdf, r, c))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
}

static t_bool	draw_line_diagonal_con1(int z[][2], t_fdf *fdf, int r, int c)
{
	if (((z[0][0] == z[0][1] && z[0][0] == z[1][0] && z[0][0] != z[1][1])
		|| (z[1][1] == z[0][1] && z[1][1] == z[1][0] && z[1][1] != z[0][0]))
		&& (in_window(fdf, fdf->map_ptr->map[r][c]) || in_window(fdf, fdf->map_ptr->map[r + 1][c + 1])))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	draw_line_diagonal_con2(int z[][2], t_fdf *fdf, int r, int c)
{
	if (((z[0][1] == z[0][0] && z[0][1] == z[1][1] && z[0][1] != z[1][0])
		|| (z[1][0] == z[0][0] && z[1][0] == z[1][1] && z[1][0] != z[0][1]))
		&& (in_window(fdf, fdf->map_ptr->map[r][c + 1]) || in_window(fdf, fdf->map_ptr->map[r + 1][c])))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	draw_line_diagonal_con3(int z[][2], t_fdf *fdf, int r, int c)
{
	if ((z[0][0] < z[0][1] && z[0][0] < z[1][0] && z[1][1] < z[0][1] && z[1][1] < z[1][0])
	&& (in_window(fdf, fdf->map_ptr->map[r][c]) || in_window(fdf, fdf->map_ptr->map[r + 1][c + 1])))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	draw_line_diagonal_con4(int z[][2], t_fdf *fdf, int r, int c)
{
	if ((z[1][0] < z[1][1] && z[1][0] < z[0][0] && z[0][1] < z[1][1] && z[0][1] < z[0][0])
	&& (in_window(fdf, fdf->map_ptr->map[r][c + 1]) || in_window(fdf, fdf->map_ptr->map[r + 1][c])))
		return (TRUE);
	else
		return (FALSE);
}
