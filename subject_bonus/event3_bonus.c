/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:59:24 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:55:46 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	mouse_drag_l(int x, int y, t_fdf *fdf);
static void	mouse_drag_r(int x, int y, t_fdf *fdf);

int	mouse_drag(int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (fdf->l_mouse_clk)
			mouse_drag_l(x, y, fdf);
		else if (fdf->r_mouse_clk)
			mouse_drag_r(x, y, fdf);
	}
	return (0);
}

static void	mouse_drag_l(int x, int y, t_fdf *fdf)
{
	int	dx;
	int	dy;

	dx = x - fdf->old_x;
	dy = y - fdf->old_y;
	if (dx != 0)
	{
		fdf->x2d_move += dx;
		fdf->flag |= MOVE_FLAG;
	}
	if (dy != 0)
	{
		fdf->y2d_move += dy;
		fdf->flag |= MOVE_FLAG;
	}
	fdf->old_x = x;
	fdf->old_y = y;
}

static void	mouse_drag_r(int x, int y, t_fdf *fdf)
{
	int	dx;
	int	dy;

	dx = x - fdf->old_x;
	dy = y - fdf->old_y;
	if (dy > 0)
		image_rotate(S_KEY, fdf);
	else if (dy < 0)
		image_rotate(W_KEY, fdf);
	if (225 < fdf->dtheta || fdf->dtheta <= 45)
	{	
		if (dx > 0)
			image_rotate(A_KEY, fdf);
		else if (dx < 0)
			image_rotate(D_KEY, fdf);
	}
	else
	{
		if (dx > 0)
			image_rotate(D_KEY, fdf);
		else if (dx < 0)
			image_rotate(A_KEY, fdf);
	}
	fdf->old_x = x;
	fdf->old_y = y;
}
