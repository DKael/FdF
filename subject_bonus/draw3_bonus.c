/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:17:09 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/23 17:57:17 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	mlx_pixel_put_at_mem(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;
	
	x += fdf->x2d_move;
	y += fdf->y2d_move;
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		dst = fdf->img_addr[fdf->cur_image] + (y * fdf->size_line[fdf->cur_image] + x * (fdf->bpp[fdf->cur_image] / 8));
		*(unsigned int *)dst = color;
	}
}

void	mlx_pixels_put_at_mem(t_fdf *fdf, t_point *p_box, t_color *c_box, int num)
{
	char	*dst;
	int		idx;
	int		x;
	int		y;

	idx = -1;
	while (++idx < num)
	{
		x = p_box[idx].rx2d + fdf->x2d_move;
		y = p_box[idx].ry2d + fdf->y2d_move;
		if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
		{
			dst = fdf->img_addr[fdf->cur_image] + (y * fdf->size_line[fdf->cur_image] + x * (fdf->bpp[fdf->cur_image] / 8));
			*(unsigned int *)dst = c_box[idx].color;
		}
	}
}

t_color	*calc_color(t_color sp, t_color bp, int np)
{
	double	color_dif[4];
	t_color	*c_box;
	int		idx;
	int		idx1;

	c_box = (t_color *)malloc(sizeof(t_color) * np);
	if (c_box == T_NULL)
		return (T_NULL);
	idx = -1;
	while (++idx < 4)
		color_dif[idx] = ((int)bp.trgb[idx] - (int)sp.trgb[idx])
			/ (double)np;
	idx1 = -1;
	while (++idx1 < np)
	{
		idx = -1;
		while (++idx < 4)
			c_box[idx1].trgb[idx] = (unsigned char)
				((double)sp.trgb[idx]
					+ color_dif[idx] * (idx1 + 1) + 0.5);
	}
	return (c_box);
}
