/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:27:35 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 22:10:38 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf1(char **argv)
{
	t_map	map;
	t_fdf	fdf;

	map = map_parsing1(argv);
	convert_point(&map);
	calc_win_size1(&map);
	fdf_init(&fdf, &map);
	enlarge_image(&map);
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == T_NULL)
	{
		free_2d_array((void *)map.map);
		exit(1);
	}
	fdf2(&fdf, &map);
}

int	loop_func(t_fdf *fdf)
{
	if (fdf->loc_change == TRUE || fdf->zoom_change == TRUE || fdf->rotate_change == TRUE)
	{
		if (fdf->rotate_change == TRUE)
		{
			rotate_point(fdf->map_ptr, fdf->alpha, fdf->beta);
			enlarge_image(fdf->map_ptr);
		}
		else if (fdf->zoom_change == TRUE)
			enlarge_image(fdf->map_ptr);
		screen_clear(fdf);
		draw(fdf, fdf->map_ptr);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
		fdf->loc_change = FALSE;
		fdf->zoom_change = FALSE;
		fdf->rotate_change = FALSE;
	}
	return (0);
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
	draw(fdf, fdf->map_ptr);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	mlx_hook(fdf->win_ptr, 2, 0, key_event, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, press_cross_on_window_frame, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_event, fdf);
	mlx_loop_hook(fdf->mlx_ptr, loop_func, fdf);
	mlx_loop(fdf->mlx_ptr);
}
