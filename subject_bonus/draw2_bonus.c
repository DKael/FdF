/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:05:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 16:35:52 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line_move_x2(t_fdf *fdf, t_point sxp, t_point bxp);
static void	draw_line_move_y2(t_fdf *fdf, t_point syp, t_point byp);

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
	t_point	*point_box;
	int		idx;
	int		np;

	np = bxp.rx2d - sxp.rx2d - 1;
	color_box = calc_color(sxp, bxp, np);
	if (color_box == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		err_msg("malloc error!", 1, FALSE);
	}
	point_box = (t_point *)malloc(sizeof(t_point) * np);
	if (point_box == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		free(color_box);
		err_msg("malloc error!", 1, FALSE);
	}
	idx = -1;
	while (++idx < np)
	{
		point_box[idx].rx2d = sxp.rx2d + 1 + idx;
		point_box[idx].ry2d = (int)(((double)(bxp.ry2d - sxp.ry2d) / (bxp.rx2d - sxp.rx2d))
				* (point_box[idx].rx2d - bxp.rx2d) + bxp.ry2d + 0.5);
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}

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
	t_point	*point_box;
	int		idx;
	int		np;

	np = byp.ry2d - syp.ry2d - 1;
	color_box = calc_color(syp, byp, np);
	if (color_box == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		err_msg("malloc error!", 1, FALSE);
	}
	point_box = (t_point *)malloc(sizeof(t_point) * np);
	if (point_box == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		free(color_box);
		err_msg("malloc error!", 1, FALSE);
	}
	idx = -1;
	while (++idx < np)
	{
		point_box[idx].ry2d = syp.ry2d + 1 + idx;
		point_box[idx].rx2d = (int)(((double)(byp.rx2d - syp.rx2d) / (byp.ry2d - syp.ry2d))
				* (point_box[idx].ry2d - byp.ry2d) + byp.rx2d + 0.5);
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}
