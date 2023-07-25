/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:27:35 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 14:13:02 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf1(char **argv)
{
	t_map	map;
	t_fdf	fdf;

	map = map_parsing(argv);
	convert_point(&map);
	calc_win_size(&map);
	fdf_init(&fdf, &map);
	enlarge_image(&map);
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == T_NULL)
	{
		free_2d_array((void *)map.map);
		exit(1);
	}
	fdf2(&fdf, &map);
	free_2d_array((void *)map.map);
}

void	fdf2(t_fdf *fdf, t_map *map)
{
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y, "fdf");
	if (fdf->win_ptr == T_NULL)
	{
		free_2d_array((void *)map->map);
		exit(1);
	}
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y);
	if (fdf->img_ptr == T_NULL)
	{
		free_2d_array((void *)map->map);
		exit(1);
	}
	fdf->img_addr = mlx_get_data_addr(fdf->img_ptr,
			&(fdf->bpp), &(fdf->size_line), &(fdf->endian));
	draw(fdf, map);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	mlx_key_hook(fdf->win_ptr, quit_program, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, press_cross_on_window_frame, fdf);
	mlx_loop(fdf->mlx_ptr);
}
