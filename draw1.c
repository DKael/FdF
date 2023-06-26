/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:37:34 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/26 21:03:06 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int	dx;
	int	dy;

	dx = abs(p1.rx_2d - p2.rx_2d);
	dy = abs(p1.ry_2d - p2.ry_2d);
	if (dx == 0 && dy == 0)
		return ;
	else if (dx == 0)
		draw_vertical_line(fdf, p1, p2);
	else if (dy == 0)
		draw_horizontal_line(fdf, p1, p2);
	else if (dx == dy)
		draw_line_slope_abs1(fdf, p1, p2);
	else if (dx > dy)
		draw_line_move_x1(fdf, p1, p2);
	else if (dx < dy)
		draw_line_move_y1(fdf, p1, p2);
}

void	draw_vertical_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	syp;
	t_point	byp;
	int		y;
	t_color	*color_box;
	int		idx;

	if (p1.ry_2d < p2.ry_2d)
	{
		syp = p1;
		byp = p2;
	}
	else
	{
		syp = p2;
		byp = p1;
	}
	y = syp.ry_2d;
	color_box = calc_color(syp, byp, byp.ry_2d - syp.ry_2d - 1);
	idx = -1;
	while (++y < byp.ry_2d)
		mlx_pixel_put_at_mem(fdf, p1.rx_2d, y, color_box[++idx].color);
	free(color_box);
}

void	draw_horizontal_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	sxp;
	t_point	bxp;
	int		x;
	t_color	*color_box;
	int		idx;

	if (p1.rx_2d < p2.rx_2d)
	{
		sxp = p1;
		bxp = p2;
	}
	else
	{
		sxp = p2;
		bxp = p1;
	}
	x = sxp.rx_2d;
	color_box = calc_color(sxp, bxp, bxp.rx_2d - sxp.rx_2d - 1);
	idx = -1;
	while (++x < bxp.rx_2d)
		mlx_pixel_put_at_mem(fdf, x, p1.ry_2d, color_box[++idx].color);
	free(color_box);
}

void	draw_line_slope_abs1(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	sxp;
	t_point	bxp;
	int		y;

	if (p1.rx_2d < p2.rx_2d)
	{
		sxp = p1;
		bxp = p2;
		y = p1.ry_2d;
	}
	else
	{
		sxp = p2;
		bxp = p1;
		y = p2.ry_2d;
	}
	draw_line_slope_abs2(fdf, sxp, bxp, y);
}

void	draw_line_slope_abs2(t_fdf *fdf, t_point sxp, t_point bxp, int y)
{
	int		x;
	int		move;
	t_color	*color_box;
	int		idx;

	x = sxp.rx_2d;
	move = -1;
	if ((bxp.rx_2d - sxp.rx_2d) / (bxp.ry_2d - sxp.ry_2d) == 1)
		move = 1;
	color_box = calc_color(sxp, bxp, bxp.rx_2d - sxp.rx_2d - 1);
	idx = -1;
	while (++x < bxp.rx_2d)
	{
		y += move;
		mlx_pixel_put_at_mem(fdf, x, y, color_box[++idx].color);
	}
	free(color_box);
}
