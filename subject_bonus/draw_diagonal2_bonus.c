/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:49:14 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 20:00:41 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_bool	draw_line_diagonal_con5(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[2] < z[3] && z[2] < z[0] && z[1] > z[3] && z[1] > z[0])
		|| (z[2] > z[3] && z[2] > z[0] && z[1] < z[3] && z[1] < z[0]))
		&& (in_window(fdf, fdf->map_ptr->map[r][c]) || in_window(fdf, fdf->map_ptr->map[r + 1][c + 1])))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con6(int *z, t_fdf *fdf, int r, int c)
{
	if (((z[0] < z[1] && z[0] < z[2] && z[3] > z[1] && z[3] > z[2])
		|| (z[0] > z[1] && z[0] > z[2] && z[3] < z[1] && z[3] < z[2]))
		&& (in_window(fdf, fdf->map_ptr->map[r][c + 1]) || in_window(fdf, fdf->map_ptr->map[r + 1][c])))
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
		&& (in_window(fdf, fdf->map_ptr->map[r][c]) || in_window(fdf, fdf->map_ptr->map[r + 1][c + 1])))
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
		&& (in_window(fdf, fdf->map_ptr->map[r][c + 1]) || in_window(fdf, fdf->map_ptr->map[r + 1][c])))
		return (TRUE);
	else
		return (FALSE);
}
