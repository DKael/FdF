/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw7_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:04:20 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:26 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line_move_y2(t_fdf *fdf, t_point syp, t_point byp);
static void	draw_line_move_y3(t_fdf *fdf,
				t_point syp, t_point byp, t_color	*color_box);

void	draw_line_move_y(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	syp;
	t_point	byp;

	if (p1.ry2d < p2.ry2d)
	{
		syp = p1;
		byp = p2;
	}
	else
	{
		syp = p2;
		byp = p1;
	}
	draw_line_move_y2(fdf, syp, byp);
}

static void	draw_line_move_y2(t_fdf *fdf, t_point syp, t_point byp)
{
	t_color	*color_box;
	int		np;

	np = byp.ry2d - syp.ry2d - 1;
	if (fdf->color_mode == 0)
		color_box = calc_color(syp.color, byp.color, np);
	else
		color_box = calc_color(fdf->contour_color[(int)(syp.z
					- fdf->map_ptr->smallest_z)], fdf->contour_color[(int)(byp.z
					- fdf->map_ptr->smallest_z)], np);
	if (color_box == T_NULL)
	{
		fdf_free(fdf);
		err_msg("malloc error!", 1, FALSE);
	}
	draw_line_move_y3(fdf, syp, byp, color_box);
}

static void	draw_line_move_y3(t_fdf *fdf,
				t_point syp, t_point byp, t_color	*color_box)
{
	t_point	*point_box;
	int		idx;
	int		np;

	np = byp.ry2d - syp.ry2d - 1;
	point_box = (t_point *)malloc(sizeof(t_point) * np);
	if (point_box == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		free(fdf->contour_color);
		free(color_box);
		err_msg("malloc error!", 1, FALSE);
	}
	idx = -1;
	while (++idx < np)
	{
		point_box[idx].ry2d = syp.ry2d + 1 + idx;
		point_box[idx].rx2d = (int)(((double)(byp.rx2d - syp.rx2d)
					/ (byp.ry2d - syp.ry2d))
				* (point_box[idx].ry2d - byp.ry2d) + byp.rx2d + 0.5);
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}
