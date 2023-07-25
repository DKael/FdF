/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_calc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:33:55 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:39:21 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	make_contour_color2(t_fdf *fdf, int z_size);

void	make_contour_color(t_fdf *fdf, t_map *map)
{
	int		z_size;

	z_size = (int)(map->largest_z - map->smallest_z + 1);
	fdf->contour_color = (t_color *)malloc(sizeof(t_color) * z_size);
	if (fdf->contour_color == T_NULL)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		err_msg("malloc error!", 1, FALSE);
	}
	fdf->contour_color[0].color = 0xFFFFFF;
	fdf->contour_color[z_size - 1].color = 0xFF0000;
	make_contour_color2(fdf, z_size);
}

static void	make_contour_color2(t_fdf *fdf, int z_size)
{
	double	color_dif[4];
	int		idx;
	int		idx1;

	idx = -1;
	while (++idx < 4)
		color_dif[idx] = ((int)fdf->contour_color[z_size - 1].trgb[idx]
				- (int)fdf->contour_color[0].trgb[idx]) / (double)z_size;
	idx1 = 0;
	while (++idx1 < z_size - 1)
	{
		idx = -1;
		while (++idx < 4)
			fdf->contour_color[idx1].trgb[idx] = (unsigned char)
				((double)fdf->contour_color[0].trgb[idx]
					+ color_dif[idx] * idx1 + 0.5);
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
