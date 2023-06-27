/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:48:23 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 13:14:35 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_line_diagonal(t_fdf *fdf, t_map *map, int r, int c)
{
	int	z00;
	int	z01;
	int	z10;
	int	z11;

	z00 = map->map[r][c].z;
	z01 = map->map[r][c + 1].z;
	z10 = map->map[r + 1][c].z;
	z11 = map->map[r + 1][c + 1].z;
	if (draw_line_diagonal_con1(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (draw_line_diagonal_con2(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (z00 < z01 && z00 < z10 && z11 < z01 && z11 < z10)
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (z10 < z11 && z10 < z00 && z01 < z11 && z01 < z00)
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con3(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
	else if (draw_line_diagonal_con4(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con5(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c + 1], map->map[r + 1][c]);
	else if (draw_line_diagonal_con6(z00, z01, z10, z11))
		draw_line(fdf, map->map[r][c], map->map[r + 1][c + 1]);
}

t_bool	is_flat(t_point p1, t_point p2, t_point p3, t_point p4)
{
	if ((p2.x - p1.x == p4.x - p3.x
			&& p2.y - p1.y == p4.y - p3.y
			&& p2.z - p1.z == p4.z - p3.z)
		&& (p1.x - p3.x == p2.x - p4.x
			&& p1.y - p3.y == p2.y - p4.y
			&& p1.z - p3.z == p2.z - p4.z))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con1(int z00, int z01, int z10, int z11)
{
	if ((z00 == z01 && z00 == z10 && z00 != z11)
		|| (z11 == z01 && z11 == z10 && z11 != z00))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con2(int z00, int z01, int z10, int z11)
{
	if ((z01 == z00 && z01 == z11 && z01 != z10)
		|| (z10 == z00 && z10 == z11 && z10 != z01))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con3(int z00, int z01, int z10, int z11)
{
	if ((z10 < z11 && z10 < z00 && z01 > z11 && z01 > z00)
		|| (z10 > z11 && z10 > z00 && z01 < z11 && z01 < z00))
		return (TRUE);
	else
		return (FALSE);
}
