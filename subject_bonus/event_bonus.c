/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 11:16:43 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	image_move(int keycode, t_fdf *fdf);
static void	image_rotate(int keycode, t_fdf *fdf);
static void	move_speed(int keycode, t_fdf *fdf);

int	press_cross_on_window_frame(t_fdf *fdf)
{
	free_2d_array((void *)fdf->map_ptr->map);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

int	key_event(int keycode, t_fdf *fdf)
{
	if(keycode == 123 || keycode == 124 || keycode == 125
		|| keycode == 126)
		image_move(keycode, fdf);
	else if (keycode == 0 || keycode == 1 || keycode == 2
		|| keycode == 13)
		image_rotate(keycode, fdf);
	else if (keycode == 24 || keycode == 27 || keycode == 33
		|| keycode == 30)
		move_speed(keycode, fdf);
	else if (keycode == 53)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	return (0);
}

static void	image_move(int keycode, t_fdf *fdf)
{
	if(keycode == 123)
	{
		fdf->x2d_move += fdf->move_speed;
		fdf->loc_change = TRUE;
	}
	else if(keycode == 124)
	{
		fdf->x2d_move -= fdf->move_speed;
		fdf->loc_change = TRUE;
	}
	if(keycode == 126)
	{
		fdf->y2d_move += fdf->move_speed;
		fdf->loc_change = TRUE;
	}
	else if(keycode == 125)
	{
		fdf->y2d_move -= fdf->move_speed;
		fdf->loc_change = TRUE;
	}
}

static void	move_speed(int keycode, t_fdf *fdf)
{
	if (keycode == 24 && fdf->move_speed < 100)
		fdf->move_speed += 1;
	else if (keycode == 27 && fdf->move_speed > 0)
		fdf->move_speed -= 1;
	else if (keycode == 30 && fdf->rot_speed < 180)
		fdf->rot_speed += 1;
	else if (keycode == 33 && fdf->rot_speed > 1)
		fdf->rot_speed -= 1;
}

static void image_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == 1)
	{
		fdf->dtheta += fdf->rot_speed;
		if (fdf->dtheta >= 360)
			fdf->dtheta -= 360;
		fdf->rotate_change = TRUE;
	}
	else if (keycode == 13)
	{
		fdf->dtheta -= fdf->rot_speed;
		if (fdf->dtheta < 0)
			fdf->dtheta += 360;
		fdf->rotate_change = TRUE;
	}
	if (keycode == 2)
	{
		fdf->dphi += fdf->rot_speed;
		if (fdf->dphi >= 360)
			fdf->dphi -= 360;
		fdf->rotate_change = TRUE;
		fdf->rotate_change = TRUE;
	}
	else if (keycode == 0)
	{
		fdf->dphi -= fdf->rot_speed;
		if (fdf->dphi < 0)
			fdf->dphi += 360;
		fdf->rotate_change = TRUE;
	}
}

int mouse_click(int button, int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (button == 1)
			fdf->l_mouse_clk = TRUE;
		if (button == 2)
			fdf->l_mouse_clk = TRUE;
		if (button == 4 && fdf->map_ptr->basic_len < 200.0)
		{
			fdf->map_ptr->basic_len += 0.5;
			if (fdf->map_ptr->basic_len > 200.0)
				fdf->map_ptr->basic_len = 200.0;
			fdf->zoom_change = TRUE;
		}
		else if (button == 5 && fdf->map_ptr->basic_len > 0.0)
		{
			fdf->map_ptr->basic_len -= 0.5;
			if (fdf->map_ptr->basic_len <= 0.0)
				fdf->map_ptr->basic_len = 0.1;
			fdf->zoom_change = TRUE;
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (button == 1)
			fdf->l_mouse_clk = FALSE;
			if (button == 1)
			fdf->l_mouse_clk = FALSE;
	}
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (fdf->l_mouse_clk)
		{
			printf("x : %d, y : %d\n", x, y);
		}
	}
	return (0);
}
