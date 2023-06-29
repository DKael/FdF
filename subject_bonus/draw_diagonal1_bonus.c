/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:48:23 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/28 09:51:17 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_bool	draw_line_diagonal_con1(int z00, int z01, int z10, int z11);
static t_bool	draw_line_diagonal_con2(int z00, int z01, int z10, int z11);
static t_bool	draw_line_diagonal_con3(int z00, int z01, int z10, int z11);
static t_bool	draw_line_diagonal_con4(int z00, int z01, int z10, int z11);
extern t_bool	draw_line_diagonal_con5(int z00, int z01, int z10, int z11);
extern t_bool	draw_line_diagonal_con6(int z00, int z01, int z10, int z11);

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



static t_bool	draw_line_diagonal_con1(int z00, int z01, int z10, int z11)
{
	if ((z00 == z01 && z00 == z10 && z00 != z11)
		|| (z11 == z01 && z11 == z10 && z11 != z00))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	draw_line_diagonal_con2(int z00, int z01, int z10, int z11)
{
	if ((z01 == z00 && z01 == z11 && z01 != z10)
		|| (z10 == z00 && z10 == z11 && z10 != z01))
		return (TRUE);
	else
		return (FALSE);
}

static t_bool	draw_line_diagonal_con3(int z00, int z01, int z10, int z11)
{
	if ((z10 < z11 && z10 < z00 && z01 > z11 && z01 > z00)
		|| (z10 > z11 && z10 > z00 && z01 < z11 && z01 < z00))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con4(int z00, int z01, int z10, int z11)
{
	if ((z00 < z01 && z00 < z10 && z11 > z01 && z11 > z10)
		|| (z00 > z01 && z00 > z10 && z11 < z01 && z11 < z10))
		return (TRUE);
	else
		return (FALSE);
}
