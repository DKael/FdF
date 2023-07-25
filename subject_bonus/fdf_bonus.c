/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:27:35 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:43:23 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fdf2(t_fdf *fdf);
static void	fdf3(t_fdf *fdf);
static int	loop_func(t_fdf *fdf);

void	fdf(char **argv)
{
	t_map	map;
	t_fdf	fdf;

	map = map_parsing(argv);
	convert_point(&map);
	isometric_projection(&map);
	get_map_data(&map);
	fdf_init(&fdf, &map);
	make_contour_color(&fdf, &map);
	enlarge_image(&map);
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == T_NULL)
	{
		fdf_free(&fdf);
		exit(1);
	}
	fdf2(&fdf);
}

static void	fdf2(t_fdf *fdf)
{
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y, "fdf");
	if (fdf->win_ptr == T_NULL)
	{
		fdf_free(fdf);
		exit(1);
	}
	fdf->img_ptr[0] = mlx_new_image(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y);
	if (fdf->img_ptr[0] == T_NULL)
	{
		fdf_free(fdf);
		exit(1);
	}
	fdf->img_ptr[1] = mlx_new_image(fdf->mlx_ptr,
			fdf->win_size_x, fdf->win_size_y);
	if (fdf->img_ptr[1] == T_NULL)
	{
		fdf_free(fdf);
		exit(1);
	}
	fdf3(fdf);
}

static void	fdf3(t_fdf *fdf)
{
	fdf->img_addr[0] = mlx_get_data_addr(fdf->img_ptr[0],
			&(fdf->bpp[0]), &(fdf->size_line[0]), &(fdf->endian[0]));
	fdf->img_addr[1] = mlx_get_data_addr(fdf->img_ptr[1],
			&(fdf->bpp[1]), &(fdf->size_line[1]), &(fdf->endian[1]));
	draw(fdf, fdf->map_ptr);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img_ptr[fdf->cur_image], 0, 0);
	mlx_hook(fdf->win_ptr, KEYPRESS, 0, key_event, fdf);
	mlx_hook(fdf->win_ptr, BUTTONPRESS, 0, mouse_event, fdf);
	mlx_hook(fdf->win_ptr, BUTTONRELEASE, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, MOTIONNOTIFY, 0, mouse_drag, fdf);
	mlx_hook(fdf->win_ptr, DESTROYNOTIFY, 0, press_cross_on_window_frame, fdf);
	mlx_loop_hook(fdf->mlx_ptr, loop_func, fdf);
	mlx_loop(fdf->mlx_ptr);
}

static int	loop_func(t_fdf *fdf)
{
	if (fdf->flag != 0)
	{
		if (fdf->cur_image == 0)
			fdf->cur_image = 1;
		else
			fdf->cur_image = 0;
		if (fdf->flag & ZOOM_FLAG || fdf->flag
			& ROTATE_FLAG || fdf->flag & PROJ_FLAG)
		{
			if (fdf->flag & ROTATE_FLAG)
				get_rotated_point(fdf->map_ptr, fdf->dtheta, fdf->dphi);
			if (fdf->projection == 1)
				perspective_projection(fdf->map_ptr);
			else
				isometric_projection(fdf->map_ptr);
			enlarge_image(fdf->map_ptr);
		}
		draw(fdf, fdf->map_ptr);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
			fdf->img_ptr[fdf->cur_image], 0, 0);
		screen_clear(fdf, 1 - 1 * (fdf->cur_image == 1));
		fdf->flag = 0;
	}
	return (0);
}
