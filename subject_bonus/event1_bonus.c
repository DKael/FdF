/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 19:13:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	image_move(int keycode, t_fdf *fdf);
static void	move_speed(int keycode, t_fdf *fdf);

int	press_cross_on_window_frame(t_fdf *fdf)
{
	fdf_free(fdf);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

int	key_event(int key, t_fdf *fdf)
{
	if (key == LEFT_KEY || key == RIGHT_KEY || key == DOWN_KEY || key == UP_KEY)
		image_move(key, fdf);
	else if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
		image_rotate(key, fdf);
	else if (key == PL_KEY || key == MN_KEY || key == SBO_KEY || key == SBC_KEY)
		move_speed(key, fdf);
	else if (key == T_KEY)
	{
		fdf->projection = 1 - 1 * fdf->projection;
		fdf->flag |= PROJ_FLAG;
	}
	else if (key == C_KEY)
	{
		fdf->color_mode = 1 - 1 * fdf->color_mode;
		fdf->flag |= COLOR_FLAG;
	}
	else if (key == ESC_KEY)
	{
		fdf_free(fdf);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	return (0);
}

static void	image_move(int keycode, t_fdf *fdf)
{
	if (keycode == LEFT_KEY)
		fdf->x2d_move += fdf->move_speed;
	else if (keycode == RIGHT_KEY)
		fdf->x2d_move -= fdf->move_speed;
	if (keycode == UP_KEY)
		fdf->y2d_move += fdf->move_speed;
	else if (keycode == DOWN_KEY)
		fdf->y2d_move -= fdf->move_speed;
	fdf->flag |= MOVE_FLAG;
}

static void	move_speed(int keycode, t_fdf *fdf)
{
	if (keycode == PL_KEY && fdf->move_speed < 100)
		fdf->move_speed += 1;
	else if (keycode == MN_KEY && fdf->move_speed > 0)
		fdf->move_speed -= 1;
	else if (keycode == SBC_KEY && fdf->rot_speed < 180)
		fdf->rot_speed += 1;
	else if (keycode == SBO_KEY && fdf->rot_speed > 1)
		fdf->rot_speed -= 1;
}

void	image_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == S_KEY)
	{
		fdf->dtheta += fdf->rot_speed;
		if (fdf->dtheta >= 360)
			fdf->dtheta -= 360;
	}
	else if (keycode == W_KEY)
	{
		fdf->dtheta -= fdf->rot_speed;
		if (fdf->dtheta < 0)
			fdf->dtheta += 360;
	}
	if (keycode == D_KEY)
	{
		fdf->dphi += fdf->rot_speed;
		if (fdf->dphi >= 360)
			fdf->dphi -= 360;
	}
	else if (keycode == A_KEY)
	{
		fdf->dphi -= fdf->rot_speed;
		if (fdf->dphi < 0)
			fdf->dphi += 360;
	}
	fdf->flag |= ROTATE_FLAG;
}
