/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw6_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:05:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:28 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line_move_x2(t_fdf *fdf, t_point sxp, t_point bxp);
static void	draw_line_move_x3(t_fdf *fdf,
				t_point sxp, t_point bxp, t_color *color_box);

void	draw_line_move_x(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	sxp;
	t_point	bxp;

	if (p1.rx2d < p2.rx2d)
	{
		sxp = p1;
		bxp = p2;
	}
	else
	{
		sxp = p2;
		bxp = p1;
	}
	draw_line_move_x2(fdf, sxp, bxp);
}

static void	draw_line_move_x2(t_fdf *fdf, t_point sxp, t_point bxp)
{
	t_color	*color_box;
	int		np;

	np = bxp.rx2d - sxp.rx2d - 1;
	if (fdf->color_mode == 0)
		color_box = calc_color(sxp.color, bxp.color, np);
	else
		color_box = calc_color(fdf->contour_color[(int)(sxp.z
					- fdf->map_ptr->smallest_z)], fdf->contour_color[(int)(bxp.z
					- fdf->map_ptr->smallest_z)], np);
	if (color_box == T_NULL)
	{
		fdf_free(fdf);
		err_msg("malloc error!", 1, FALSE);
	}
	draw_line_move_x3(fdf, sxp, bxp, color_box);
}

static void	draw_line_move_x3(t_fdf *fdf,
				t_point sxp, t_point bxp, t_color *color_box)
{
	t_point	*point_box;
	int		idx;
	int		np;

	np = bxp.rx2d - sxp.rx2d - 1;
	point_box = (t_point *)malloc(sizeof(t_point) * np);
	if (point_box == T_NULL)
	{
		fdf_free(fdf);
		free(color_box);
		err_msg("malloc error!", 1, FALSE);
	}
	idx = -1;
	while (++idx < np)
	{
		point_box[idx].rx2d = sxp.rx2d + 1 + idx;
		point_box[idx].ry2d = (int)(((double)(bxp.ry2d - sxp.ry2d)
					/ (bxp.rx2d - sxp.rx2d))
				* (point_box[idx].rx2d - bxp.rx2d) + bxp.ry2d + 0.5);
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}
