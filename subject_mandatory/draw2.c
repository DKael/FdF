/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:05:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/26 21:03:21 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_move_x1(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	sxp;
	t_point	bxp;

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
	draw_line_move_x2(fdf, sxp, bxp);
}

void	draw_line_move_x2(t_fdf *fdf, t_point sxp, t_point bxp)
{
	int		x;
	int		y;
	t_color	*color_box;
	int		idx;

	x = sxp.rx_2d;
	color_box = calc_color(sxp, bxp, bxp.rx_2d - sxp.rx_2d - 1);
	idx = -1;
	while (++x < bxp.rx_2d)
	{
		y = (int)(((double)(bxp.ry_2d - sxp.ry_2d) / (bxp.rx_2d - sxp.rx_2d))
				* (x - bxp.rx_2d) + bxp.ry_2d + 0.5);
		mlx_pixel_put_at_mem(fdf, x, y, color_box[++idx].color);
	}
	free(color_box);
}

void	draw_line_move_y1(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	syp;
	t_point	byp;

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
	draw_line_move_y2(fdf, syp, byp);
}

void	draw_line_move_y2(t_fdf *fdf, t_point syp, t_point byp)
{
	int		x;
	int		y;
	t_color	*color_box;
	int		idx;

	y = syp.ry_2d;
	color_box = calc_color(syp, byp, byp.ry_2d - syp.ry_2d - 1);
	idx = -1;
	while (++y < byp.ry_2d)
	{
		x = (int)(((double)(byp.rx_2d - syp.rx_2d) / (byp.ry_2d - syp.ry_2d))
				* (y - byp.ry_2d) + byp.rx_2d + 0.5);
		mlx_pixel_put_at_mem(fdf, x, y, color_box[++idx].color);
	}
	free(color_box);
}
