/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 15:18:26 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	quit_program(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	return (0);
}

int	press_cross_on_window_frame(t_fdf *fdf)
{
	free_2d_array((void *)fdf->map_ptr->map);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}
