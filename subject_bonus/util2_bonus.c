/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:36:11 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 19:36:47 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_bool	should_draw_line2(t_fdf *fdf, int p[]);

t_bool	should_draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int		p[4];

	p[0] = p1.rx2d + fdf->x2d_move;
	p[1] = p2.rx2d + fdf->x2d_move;
	p[2] = p1.ry2d + fdf->y2d_move;
	p[3] = p2.ry2d + fdf->y2d_move;
	if (p[1] != p[0])
		return (should_draw_line2(fdf, p));
	else
		if (0 <= p[1] && p[1] < fdf->win_size_x && !((p[3] < 0 && p[2] < 0)
				|| (p[3] >= fdf->win_size_y && p[2] >= fdf->win_size_y)))
			return (TRUE);
	return (FALSE);
}

static t_bool	should_draw_line2(t_fdf *fdf, int p[])
{
	double	slope;

	slope = ((double)(p[3] - p[2]) / (p[1] - p[0]));
	if (slope > 0.0)
	{
		if (p[3] - p[1] * slope < fdf->win_size_y
			&& slope * (fdf->win_size_x - 1 - p[1]) + p[3] >= 0)
			return (TRUE);
	}
	else if (slope < 0.0)
	{
		if (p[3] - slope * p[1] >= 0 && slope
			* (fdf->win_size_x - 1 - p[1]) + p[3] < fdf->win_size_y)
			return (TRUE);
	}
	else
	{
		if (0 <= p[3] && p[3] < fdf->win_size_y && !((p[1] < 0 && p[0] < 0)
				|| (p[1] >= fdf->win_size_x && p[0] >= fdf->win_size_x)))
			return (TRUE);
	}
	return (FALSE);
}

void	fdf_init(t_fdf *fdf, t_map *map)
{
	fdf->mlx_ptr = T_NULL;
	fdf->win_ptr = T_NULL;
	fdf->img_ptr[0] = T_NULL;
	fdf->img_addr[0] = T_NULL;
	fdf->img_ptr[1] = T_NULL;
	fdf->img_addr[1] = T_NULL;
	fdf->win_size_x = WINDOW_SIZE_X;
	fdf->win_size_y = WINDOW_SIZE_Y;
	fdf->map_ptr = map;
	fdf->x2d_move = 0;
	fdf->y2d_move = 0;
	fdf->flag = 0;
	fdf->move_speed = 10;
	fdf->rot_speed = 1;
	fdf->dtheta = 0;
	fdf->dphi = 0;
	fdf->l_mouse_clk = FALSE;
	fdf->r_mouse_clk = FALSE;
	fdf->old_x = -1;
	fdf->old_y = -1;
	fdf->cur_image = 0;
	fdf->projection = 0;
	fdf->color_mode = 0;
	fdf->contour_color = T_NULL;
}

void	map_init(t_map *map)
{
	map->map = T_NULL;
	map->row = 0;
	map->col = 0;
	map->fd = -1;
	map->largest_x2d = (WINDOW_SIZE_X / 2) * -1;
	map->largest_y2d = (WINDOW_SIZE_Y / 2) * -1;
	map->smallest_x2d = WINDOW_SIZE_X / 2;
	map->smallest_y2d = WINDOW_SIZE_Y / 2;
}

void	fdf_free(t_fdf *fdf)
{
	free_2d_array((void *)fdf->map_ptr->map);
	free(fdf->contour_color);
}
