/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:27:35 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/03 14:11:15 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fdf2(t_fdf *fdf, t_map *map);
static int	loop_func(t_fdf *fdf);

void	fdf(char **argv)
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
}

static void	fdf2(t_fdf *fdf, t_map *map)
{
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y, "fdf");
	if (fdf->win_ptr == T_NULL)
	{
		free_2d_array((void *)map->map);
		exit(1);
	}
	fdf->img_ptr[0] = mlx_new_image(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y);
	if (fdf->img_ptr[0] == T_NULL)
	{
		free_2d_array((void *)map->map); 
		exit(1);
	}
	fdf->img_addr[0] = mlx_get_data_addr(fdf->img_ptr[0],
			&(fdf->bpp[0]), &(fdf->size_line[0]), &(fdf->endian[0]));
	fdf->img_ptr[1] = mlx_new_image(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y);
	if (fdf->img_ptr[1] == T_NULL)
	{
		free_2d_array((void *)map->map); 
		exit(1);
	}
	fdf->img_addr[1] = mlx_get_data_addr(fdf->img_ptr[1],
			&(fdf->bpp[1]), &(fdf->size_line[1]), &(fdf->endian[1]));
	draw(fdf, fdf->map_ptr);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr[fdf->cur_image], 0, 0);
	mlx_hook(fdf->win_ptr, KEYPRESS, 0, key_event, fdf);
	mlx_hook(fdf->win_ptr, BUTTONPRESS, 0, mouse_click, fdf);
	mlx_hook(fdf->win_ptr, BUTTONRELEASE, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, MOTIONNOTIFY, 0, mouse_move, fdf);
	mlx_hook(fdf->win_ptr, DESTROYNOTIFY, 0, press_cross_on_window_frame, fdf);
	mlx_loop_hook(fdf->mlx_ptr, loop_func, fdf);
	mlx_loop(fdf->mlx_ptr);
}

int	loop_func(t_fdf *fdf)
{
	if (fdf->loc_change == TRUE || fdf->zoom_change == TRUE || fdf->rotate_change == TRUE)
	{
		if (fdf->cur_image == 0)
			fdf->cur_image = 1;
		else
			fdf->cur_image = 0;
		if (fdf->rotate_change == TRUE)
		{
			get_rotated_point(fdf->map_ptr, fdf->dtheta, fdf->dphi);
			enlarge_image(fdf->map_ptr);
		}
		else if (fdf->zoom_change == TRUE)
			enlarge_image(fdf->map_ptr);
		draw(fdf, fdf->map_ptr); 
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr[fdf->cur_image], 0, 0);
		screen_clear(fdf, 1 - 1 * (fdf->cur_image == 1));
		fdf->loc_change = FALSE;
		fdf->zoom_change = FALSE;
		fdf->rotate_change = FALSE;
	}
	return (0);
}
