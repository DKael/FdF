/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:49:14 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/03 23:44:07 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_bool	draw_line_diagonal_con5(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[2] < z[3] && z[2] < z[0] && z[1] > z[3] && z[1] > z[0])
		|| (z[2] > z[3] && z[2] > z[0] && z[1] < z[3] && z[1] < z[0]))
		&& (should_draw_line(fdf, fdf->map_ptr->map[r][c], fdf->map_ptr->map[r + 1][c + 1])))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con6(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[0] < z[1] && z[0] < z[2] && z[3] > z[1] && z[3] > z[2])
		|| (z[0] > z[1] && z[0] > z[2] && z[3] < z[1] && z[3] < z[2]))
		&& (should_draw_line(fdf, fdf->map_ptr->map[r][c + 1], fdf->map_ptr->map[r + 1][c])))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con7(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[0] >= z[1] && z[1] >= z[3] && z[3] >= z[2])
		|| (z[0] >= z[2] && z[2] >= z[3] && z[3] >= z[1])
		|| (z[3] >= z[2] && z[2] >= z[0] && z[0] >= z[1])
		|| (z[3] >= z[1] && z[1] >= z[0] && z[0] >= z[2]))
		&& (should_draw_line(fdf, fdf->map_ptr->map[r][c], fdf->map_ptr->map[r + 1][c + 1])))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con8(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[1] >= z[3] && z[3] >= z[2] && z[2] >= z[0])
		|| (z[1] >= z[0] && z[0] >= z[2] && z[2] >= z[3])
		|| (z[2] >= z[0] && z[0] >= z[1] && z[1] >= z[3])
		|| (z[2] >= z[3] && z[3] >= z[1] && z[1] >= z[0]))
		&& (should_draw_line(fdf, fdf->map_ptr->map[r][c + 1], fdf->map_ptr->map[r + 1][c])))
		return (TRUE);
	else
		return (FALSE);
}
