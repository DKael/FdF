/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:17:09 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 13:14:44 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	mlx_pixel_put_at_mem(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		dst = fdf->img_addr + (y * fdf->size_line + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_color	*calc_color(t_point sp, t_point bp, int np)
{
	double	color_dif[4];
	t_color	*c_box;
	int		idx;
	int		idx1;

	c_box = (t_color *)malloc(sizeof(t_color) * np);
	if (c_box == T_NULL)
	{
		err_msg("malloc error!", 1, FALSE);
	}
	idx = -1;
	while (++idx < 4)
		color_dif[idx] = ((int)bp.color.trgb[idx] - (int)sp.color.trgb[idx])
			/ (double)np;
	idx1 = -1;
	while (++idx1 < np)
	{
		idx = -1;
		while (++idx < 4)
			c_box[idx1].trgb[idx] = (unsigned char)
				((double)sp.color.trgb[idx]
					+ color_dif[idx] * (idx1 + 1) + 0.5);
	}
	return (c_box);
}
