/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:37:34 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 20:29:58 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line_slope_abs2(t_fdf *fdf, t_point sxp, t_point bxp);

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int	dx;
	int	dy;
	
	dx = abs(p1.rx2d - p2.rx2d);
	dy = abs(p1.ry2d - p2.ry2d);
	if (dx == 0 && dy == 0)
		return ;
	else if (dx == 0)
		draw_vertical_line(fdf, p1, p2);
	else if (dy == 0)
		draw_horizontal_line(fdf, p1, p2);
	else if (dx == dy)
		draw_line_slope_abs(fdf, p1, p2);
	else if (dx > dy)
		draw_line_move_x(fdf, p1, p2);
	else if (dx < dy)
		draw_line_move_y(fdf, p1, p2);
}

void	draw_vertical_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	syp;
	t_point	byp;
	t_color	*color_box;
	t_point	*point_box;
	int		idx;
	int		np;

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
		point_box[idx].rx2d = syp.rx2d;
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}

void	draw_horizontal_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	sxp;
	t_point	bxp;
	t_color	*color_box;
	t_point	*point_box;
	int		idx;
	int		np;

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
		point_box[idx].ry2d = sxp.ry2d;
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}

void	draw_line_slope_abs(t_fdf *fdf, t_point p1, t_point p2)
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
	draw_line_slope_abs2(fdf, sxp, bxp);
}

static void	draw_line_slope_abs2(t_fdf *fdf, t_point sxp, t_point bxp)
{
	int		move;
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
	move = -1;
	if ((bxp.rx2d - sxp.rx2d) / (bxp.ry2d - sxp.ry2d) == 1)
		move = 1;
	idx = -1;
	while (++idx < np)
	{
		point_box[idx].rx2d = sxp.rx2d + 1 + idx;
		point_box[idx].ry2d = sxp.ry2d + move * (idx + 1);
	}
	mlx_pixels_put_at_mem(fdf, point_box, color_box, np);
	free(color_box);
	free(point_box);
}
