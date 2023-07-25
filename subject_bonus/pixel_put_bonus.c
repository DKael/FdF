/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:17:09 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:08 by hyungdki         ###   ########.fr       */
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
		dst = fdf->img_addr[fdf->cur_image]
			+ (y * fdf->size_line[fdf->cur_image]
				+ x * (fdf->bpp[fdf->cur_image] / 8));
		*(unsigned int *)dst = color;
	}
}

void	mlx_pixels_put_at_mem(t_fdf *fdf,
				t_point *p_box, t_color *c_box, int num)
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
			dst = fdf->img_addr[fdf->cur_image]
				+ (y * fdf->size_line[fdf->cur_image]
					+ x * (fdf->bpp[fdf->cur_image] / 8));
			*(unsigned int *)dst = c_box[idx].color;
		}
	}
}
